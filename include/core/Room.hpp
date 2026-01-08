#pragma once
#include <climits>
#include "core/Position.hpp"
#include "data_structures/LinkedList.h"

struct Room {
    int id = -1;
    int rmin = INT_MAX;
    int rmax = -1;
    int cmin = INT_MAX;
    int cmax = -1;
    ds::LinkedList<Position> floorCells;
    int uncleanedCount = 0;
    int minDockDist = INT_MAX;
};
