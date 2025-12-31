#pragma once

#include "Position.hpp"
#include "data_structures/LinkedList.h"

struct Room {
    int id = -1;

    ds::LinkedList<Position> floorCells;

    int uncleanedCount = 0;

    int minDockDist = 0;
};
