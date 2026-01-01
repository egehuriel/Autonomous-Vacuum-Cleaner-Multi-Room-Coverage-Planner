#include "core/PathFinder.hpp"
#include "data_structures/Queues.h"
#include "data_structures/HashSet.h"


PathFinder::PathFinder(GridModel& gridModel)
    : grid(gridModel) {
    dock = grid.dockPosition;

}

int PathFinder::distanceToDock(Position start) {
    ds::Queue<Position> q;
    ds::HashSet<Position, PositionHash> visited;


    q.enqueue(start);
    visited.insert(start);

    int dist = 0;

    while (!q.isEmpty()) {
        Position cur = q.dequeue();
        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        if (cur.r == dock.r && cur.c == dock.c)
            return dist;

        for (int k = 0; k < 4; k++) {
            Position next{cur.r + dr[k], cur.c + dc[k]};

            if (next.r < 0 || next.r >= grid.rows ||
                next.c < 0 || next.c >= grid.cols)
                continue;

            if (grid.cells[next.r][next.c] == CellType::WALL)
                continue;

            if (visited.contains(next))
                continue;

            visited.insert(next);
            q.enqueue(next);
        }

        dist++;
    }

    return -1;
}

bool PathFinder::canReachDock(Position start, int battery) {
    int dist = distanceToDock(start);
    if (dist == -1) return false;
    return battery >= dist;
}
