#include "core/PathFinder.hpp"
#include "../include/data_structures/Queues.h"
#include "../include/data_structures/HashSet.h"


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
        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};

        if (cur.x == dock.x && cur.y == dock.y)
            return dist;

        for (int k = 0; k < 4; k++) {
            Position next{cur.x + dx[k], cur.y + dy[k]};

            if (next.x < 0 || next.x >= grid.rows ||
                next.y < 0 || next.y >= grid.cols)
                continue;

            if (grid.cells[next.x][next.y] == CellType::WALL)
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
