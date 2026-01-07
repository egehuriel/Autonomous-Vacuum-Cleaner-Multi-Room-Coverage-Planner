#include "PathFinder.hpp"


PathFinder::PathFinder(GridModel& gridModel)
    : grid(gridModel) {
    dock = grid.dockPosition;
}

int PathFinder::distanceToDock(Position start) {
    ds::Queue<Position> q;
    ds::HashSet<Position, PositionHash> visited;

    q.enqueue(start);
    visited.insert(start);

    std::vector<std::vector<int>> dist(
        grid.rows, std::vector<int>(grid.cols, -1)
    );
    dist[start.x][start.y] = 0;

    while (!q.isEmpty()) {
        Position cur = q.dequeue();

        if (cur.x == dock.x && cur.y == dock.y)
            return dist[cur.x][cur.y];

        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};

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
            dist[next.x][next.y] = dist[cur.x][cur.y] + 1;
            q.enqueue(next);
        }
    }

    return -1;
}

bool PathFinder::canReachDock(Position start, int battery) {
    int dist = distanceToDock(start);
    return dist != -1 && battery >= dist;
}
