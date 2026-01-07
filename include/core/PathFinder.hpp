#pragma once

#include "core/GridModel.hpp"
#include "data_structures/Queues.h"
#include "data_structures/HashSet.h"

struct PositionHash {
    int operator()(const Position& p) const {
        return p.r * 37 + p.c;
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
