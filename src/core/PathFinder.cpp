#include "core/PathFinder.hpp"
#include "data_structures/Queues.h"
#include <cstring>

PathFinder::PathFinder(GridModel& gridModel) : grid(gridModel), dock(gridModel.dockPosition) {}

int PathFinder::distanceToDock(Position start) {
    if (start == dock) return 0;
    int rows = grid.R();
    int cols = grid.C();
    int totalCells = rows * cols;
    bool* visited = new bool[totalCells];
    for(int i = 0; i < totalCells; i++) {
        visited[i] = false;
    }
    struct Node {
        Position pos;
        int dist;
    };
    ds::Queue<Node> q;
    q.enqueue({start, 0});
    int startIndex = start.r * cols + start.c;
    visited[startIndex] = true;
    int resultDist = -1;
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    while (!q.isEmpty()) {
        Node current = q.front();
        q.dequeue();
        if (current.pos == dock) {
            resultDist = current.dist;
            break;
        }
        for (int i = 0; i < 4; i++) {
            int nr = current.pos.r + dr[i];
            int nc = current.pos.c + dc[i];
            if (grid.inBounds(nr, nc)) {
                if (grid.isTraversable(nr, nc) || (nr == dock.r && nc == dock.c)) {
                    int index = nr * cols + nc;
                    if (!visited[index]) {
                        visited[index] = true;
                        q.enqueue({Position(nr, nc), current.dist + 1});
                    }
                }
            }
        }
    }
    delete[] visited;
    return resultDist;
}

bool PathFinder::canReachDock(Position start, int battery) {
    int dist = distanceToDock(start);
    if (dist == -1) return false;
    return battery >= dist;
}
