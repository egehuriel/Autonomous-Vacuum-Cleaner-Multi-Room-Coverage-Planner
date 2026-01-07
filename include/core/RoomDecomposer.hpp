#pragma once
#include "core/GridModel.hpp"
#include "core/Room.hpp"

#include "../data_structures/Queues.h"
#include "../data_structures/LinkedList.h"

class RoomDecomposer {
private:
    int** roomId;
    int roomCount;
    int lastR;

    void allocRoomId(int R, int C);
    void freeRoomId();

    void floodFillRoom(GridModel& grid, int startR, int startC, int rid, Room& outRoom);

public:
    RoomDecomposer();
    ~RoomDecomposer();

    RoomDecomposer(const RoomDecomposer&) = delete;
    RoomDecomposer& operator=(const RoomDecomposer&) = delete;

    int assignRooms(GridModel& grid, ds::LinkedList<Room>& rooms);

    int getRoomId(int r, int c) const;
    int getRoomCount() const { return roomCount; }
};