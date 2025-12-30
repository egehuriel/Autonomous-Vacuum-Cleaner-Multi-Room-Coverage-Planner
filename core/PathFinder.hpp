#pragma once

#include "../include/core/GridModel.hpp"
#include "../include/data_structures/Queues.h"
#include "../include/data_structures/HashSet.h"

struct PositionHash {
    int operator()(const Position& p) const {
        return p.x * 37 + p.y;
    }
};

class PathFinder {
private:
    GridModel& grid;
    Position dock;

public:
    PathFinder(GridModel& gridModel);
    int distanceToDock(Position start);
    bool canReachDock(Position start, int battery);
};
