#include "core/PathFinder.hpp"
#include "data_structures/Queues.h"
#include "data_structures/Stack.h"
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

int PathFinder::computeMaxDistanceFromDock() {
    int rows = grid.R();
    int cols = grid.C();
    int totalCells = rows * cols;
    
    // BFS from dock to all reachable cells
    bool* visited = new bool[totalCells];
    int* distances = new int[totalCells];
    
    for (int i = 0; i < totalCells; i++) {
        visited[i] = false;
        distances[i] = -1;
    }
    
    struct Node {
        Position pos;
        int dist;
    };
    
    ds::Queue<Node> q;
    int dockIndex = dock.r * cols + dock.c;
    visited[dockIndex] = true;
    distances[dockIndex] = 0;
    q.enqueue({dock, 0});
    
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    int maxDist = 0;
    
    while (!q.isEmpty()) {
        Node current = q.front();
        q.dequeue();
        
        if (current.dist > maxDist) {
            maxDist = current.dist;
        }
        
        for (int i = 0; i < 4; i++) {
            int nr = current.pos.r + dr[i];
            int nc = current.pos.c + dc[i];
            
            if (grid.inBounds(nr, nc)) {
                if (grid.isTraversable(nr, nc) || (nr == dock.r && nc == dock.c)) {
                    int index = nr * cols + nc;
                    if (!visited[index]) {
                        visited[index] = true;
                        distances[index] = current.dist + 1;
                        q.enqueue({Position(nr, nc), current.dist + 1});
                    }
                }
            }
        }
    }
    
    delete[] visited;
    delete[] distances;
    return maxDist;
}

bool PathFinder::getPathToDock(Position start, ds::Stack<Position>& outPath) {
    // Clear output path
    while (!outPath.isEmpty()) {
        outPath.pop();
    }
    
    if (start == dock) {
        outPath.push(dock);
        return true;
    }
    
    int rows = grid.R();
    int cols = grid.C();
    int totalCells = rows * cols;
    
    bool* visited = new bool[totalCells];
    int* parent = new int[totalCells];
    
    for (int i = 0; i < totalCells; i++) {
        visited[i] = false;
        parent[i] = -1;
    }
    
    struct Node {
        Position pos;
        int index;
    };
    
    ds::Queue<Node> q;
    int startIndex = start.r * cols + start.c;
    int dockIndex = dock.r * cols + dock.c;
    
    visited[startIndex] = true;
    q.enqueue({start, startIndex});
    
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    bool found = false;
    
    while (!q.isEmpty()) {
        Node current = q.front();
        q.dequeue();
        
        if (current.pos == dock) {
            found = true;
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
                        parent[index] = current.index;
                        q.enqueue({Position(nr, nc), index});
                    }
                }
            }
        }
    }
    
    if (!found) {
        delete[] visited;
        delete[] parent;
        return false;
    }
    
    // Reconstruct path from dock to start (will be reversed)
    ds::Stack<Position> tempPath;
    int cur = dockIndex;
    while (cur != -1) {
        int r = cur / cols;
        int c = cur % cols;
        tempPath.push(Position(r, c));
        if (cur == startIndex) break;
        cur = parent[cur];
    }
    
    // Reverse to get path from start to dock
    ds::Stack<Position> reversePath;
    while (!tempPath.isEmpty()) {
        reversePath.push(tempPath.pop());
    }
    
    // Copy to output path
    while (!reversePath.isEmpty()) {
        outPath.push(reversePath.pop());
    }
    
    delete[] visited;
    delete[] parent;
    return true;
}
