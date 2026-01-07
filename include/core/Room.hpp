#pragma once

#include "core/Position.hpp"
#include "data_structures/LinkedList.h"

struct Room {
    int id = -1;
    int rmin = 0;
    int rmax = 0;
    int cmin = 0;
    int cmax = 0;
    ds::LinkedList<Position> floorCells;

    int uncleanedCount = 0;

    int minDockDist = 0;
};
