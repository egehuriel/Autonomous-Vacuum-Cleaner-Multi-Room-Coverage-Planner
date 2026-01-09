#include <iostream>
#include <string>
#include <utility>

#include "core/GridParser.hpp"
#include "core/PathFinder.hpp"
#include "core/BatteryManager.hpp"
#include "core/RoomDecomposer.hpp"
#include "core/RoomStrategy.hpp"
#include "core/CoveragePlanner.hpp"
#include "frontend/TUI.hpp"
#include "data_structures/Queues.h"

static GridModel* g_grid = nullptr;
static PathFinder* g_pf = nullptr;
static bool g_returnRequested = false;

static int distToDockHook(const Position& p) {
    return g_pf ? g_pf->distanceToDock(p) : -1;
}

static void requestReturnHook() {
    g_returnRequested = true;
}

static bool buildPathHook(const Position& from, const Position& to, ds::Stack<Position>& outPath) {
    while (!outPath.isEmpty()) outPath.pop();
    if (!g_grid) return false;

    const int R = g_grid->R();
    const int C = g_grid->C();
    auto idx = [C](int r, int c) { return r * C + c; };

    if (!g_grid->inBounds(from.r, from.c) || !g_grid->inBounds(to.r, to.c)) return false;
    if (!g_grid->isTraversable(from.r, from.c) && !(from == g_grid->dockPosition)) return false;
    if (!g_grid->isTraversable(to.r, to.c) && !(to == g_grid->dockPosition)) return false;

    int total = R * C;
    int* parent = new int[total];
    char* vis = new char[total];

    for (int i = 0; i < total; i++) {
        parent[i] = -1;
        vis[i] = 0;
    }

    ds::Queue<Position> q;

    const int s = idx(from.r, from.c);
    const int t = idx(to.r, to.c);
    vis[s] = 1;
    q.enqueue(from);

    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    while (!q.isEmpty()) {
        Position cur = q.dequeue();
        if (cur == to) break;

        for (int k = 0; k < 4; k++) {
            int nr = cur.r + dr[k];
            int nc = cur.c + dc[k];
            if (!g_grid->inBounds(nr, nc)) continue;

            if (!g_grid->isTraversable(nr, nc) && !(Position(nr, nc) == g_grid->dockPosition)) continue;

            const int ni = idx(nr, nc);
            if (vis[ni]) continue;
            vis[ni] = 1;
            parent[ni] = idx(cur.r, cur.c);
            q.enqueue(Position(nr, nc));
        }
    }

    if (!vis[t]) {
        delete[] parent;
        delete[] vis;
        return false;
    }

    ds::Stack<Position> tmp;
    int cur = t;
    while (cur != -1) {
        int r = cur / C;
        int c = cur % C;
        tmp.push(Position(r, c));
        if (cur == s) break;
        cur = parent[cur];
    }

    while (!tmp.isEmpty()) {
        outPath.push(tmp.pop());
    }

    delete[] parent;
    delete[] vis;
    return true;
}

int main(int argc, char** argv) {
    try {
        std::string file = "data/small_room.json";
        DisplayMode mode = DisplayMode::STEP;

        if (argc >= 2) file = argv[1];
        if (argc >= 3) {
            std::string m = argv[2];
            if (m == "fast" || m == "FAST") mode = DisplayMode::FAST;
        }

        GridModel grid = GridParser::parse(file);
        PathFinder pf(grid);
        BatteryManager bm(grid.initialBattery, pf, 2);

        // Compute max distance from dock to all reachable cells
        int maxDistanceFromDock = pf.computeMaxDistanceFromDock();
        // Compute safety threshold with 7.5% buffer (between 5-10%)
        int safetyThreshold = maxDistanceFromDock + (maxDistanceFromDock * 8 / 100);
        if (safetyThreshold < maxDistanceFromDock + 1) {
            safetyThreshold = maxDistanceFromDock + 1;
        }

        RoomDecomposer decomposer;
        ds::LinkedList<Room> rooms;
        decomposer.assignRooms(grid, rooms);

        RoomStrategy strategy;

        g_pf = &pf;
        ds::LinkedList<int> roomOrder = strategy.buildRoomOrder(rooms, &distToDockHook);

        CoveragePlanner planner;
        CoveragePlanner::Hooks hooks;
        hooks.buildPath = &buildPathHook;
        hooks.distToDock = &distToDockHook;
        hooks.requestReturnToDock = &requestReturnHook;
        hooks.safetyMargin = 2;

        g_grid = &grid;
        g_returnRequested = false;
        planner.init(&grid, &rooms, &decomposer, hooks);
        planner.setRoomOrder(roomOrder);

        TUI ui;
        ui.setMode(mode);

        Position pos = grid.startPosition;
        int totalSteps = 0;
        int totalBatteryUsed = 0;
        bool returnToDockMode = false;

        if (grid.isFloor(pos.r, pos.c) && !grid.isCleaned(pos.r, pos.c)) {
            grid.markCleaned(pos.r, pos.c);
        }

        while (true) {
            // Check if we've reached the dock in return-to-dock mode
            if (returnToDockMode && pos == grid.dockPosition) {
                // Terminate execution when dock is reached
                break;
            }

            if (pos == grid.dockPosition && !returnToDockMode) {
                bm.recharge();
                g_returnRequested = false;
                returnToDockMode = false;
            }

            ui.render(grid, pos, bm.getBattery());
            ui.waitForNext();

            // Check battery before each movement cycle
            int currentBattery = bm.getBattery();
            int distanceToDock = pf.distanceToDock(pos);
            
            // If battery is insufficient to return to dock, switch to return-to-dock mode
            if (!returnToDockMode && distanceToDock >= 0 && currentBattery <= distanceToDock + safetyThreshold) {
                returnToDockMode = true;
            }

            ds::Stack<Position> path;
            bool ok = false;

            if (returnToDockMode) {
                // Get shortest path to dock
                ok = pf.getPathToDock(pos, path);
            } else if (g_returnRequested && !(pos == grid.dockPosition)) {
                ok = buildPathHook(pos, grid.dockPosition, path);
                if (ok) {
                    returnToDockMode = true;
                }
            } else {
                // Check if all floors are cleaned
                if (planner.allFloorsCleaned()) {
                    // All cleaned, return to dock
                    ok = pf.getPathToDock(pos, path);
                    if (ok) {
                        returnToDockMode = true;
                    } else {
                        break;
                    }
                } else {
                    ok = planner.planNextPath(pos, bm.getBattery(), path);
                }
            }

            Position vacuumPos = pos;
            int battery = bm.getBattery();
            Position target = vacuumPos;
            int pathLen = 0;

            {
                ds::Stack<Position> tmp1;
                ds::Stack<Position> tmp2;

                while (!path.isEmpty()) {
                    Position p = path.pop();
                    pathLen++;
                    target = p;
                    tmp1.push(std::move(p));
                }

                while (!tmp1.isEmpty()) {
                    tmp2.push(tmp1.pop());
                }

                while (!tmp2.isEmpty()) {
                    path.push(tmp2.pop());
                }
            }    

            std::cout << "[DBG] pos=(" << vacuumPos.r << "," << vacuumPos.c << ") battery=" << battery << " target=(" << target.r << "," << target.c << ")" << " pathLen=" << pathLen << " cleanedHere=" << grid.isCleaned(vacuumPos.r, vacuumPos.c) << " returnToDock=" << (returnToDockMode ? "true" : "false") << std::endl;

            if (!ok) break;
            if (path.isEmpty()) break;

            Position first = path.pop();
            (void)first;

            while (!path.isEmpty()) {
                // Check battery before each movement
                currentBattery = bm.getBattery();
                distanceToDock = pf.distanceToDock(pos);
                
                // If battery is insufficient, switch to return-to-dock mode immediately
                if (!returnToDockMode && distanceToDock >= 0 && currentBattery <= distanceToDock + safetyThreshold) {
                    returnToDockMode = true;
                    // Get path to dock and replace current path
                    ds::Stack<Position> dockPath;
                    if (pf.getPathToDock(pos, dockPath)) {
                        // Clear current path
                        while (!path.isEmpty()) path.pop();
                        // Copy dock path to current path (maintaining order: start on top, dock on bottom)
                        ds::Stack<Position> tmp;
                        while (!dockPath.isEmpty()) {
                            Position p = dockPath.pop();
                            tmp.push(p);
                        }
                        while (!tmp.isEmpty()) {
                            path.push(tmp.pop());
                        }
                    } else {
                        break;
                    }
                }

                if (currentBattery <= 0) {
                    // Battery depleted, stop
                    break;
                }

                pos = path.pop();
                bm.consume(1);
                totalSteps++;
                totalBatteryUsed++;

                if (grid.isFloor(pos.r, pos.c) && !grid.isCleaned(pos.r, pos.c)) {
                    grid.markCleaned(pos.r, pos.c);
                }

                ui.render(grid, pos, bm.getBattery());
                ui.waitForNext();

                // If we reached dock in return-to-dock mode, terminate
                if (returnToDockMode && pos == grid.dockPosition) {
                    break;
                }
            }

            // If we reached dock in return-to-dock mode, exit main loop
            if (returnToDockMode && pos == grid.dockPosition) {
                break;
            }
        }

        ui.printSummary(grid, totalSteps, totalBatteryUsed);
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Fatal: " << e.what() << std::endl;
        return 1;
    }
}