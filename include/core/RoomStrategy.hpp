#pragma once
#include "core/Room.hpp"
#include "core/GridModel.hpp"
#include "data_structures/LinkedList.h"
#include "core/Position.hpp"

class RoomStrategy {
public:
    RoomStrategy() {}

    typedef int (*DistFunc)(const Position&);

    ds::LinkedList<int> buildRoomOrder(ds::LinkedList<Room>& rooms, DistFunc distFunc);

private:
    void selectionSortByMinDockDist(Room* arr, int n); 
};