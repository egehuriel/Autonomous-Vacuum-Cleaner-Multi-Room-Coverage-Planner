#include "core/RoomDecomposer.hpp"

static const int DR[4] = {-1, 1, 0, 0};
static const int DC[4] = {0, 0, -1, 1};

RoomDecomposer::RoomDecomposer() : roomId(nullptr), roomCount(0), lastR(0) {}

RoomDecomposer::~RoomDecomposer() {
    freeRoomId();
}

void RoomDecomposer::allocRoomId(int R, int C) {
    freeRoomId();
    lastR = R;
    roomId = new int*[R];
    for (int r = 0; r < R; r++) {
        roomId[r] = new int[C];
        for (int c = 0; c < C; c++) roomId[r][c] = -1;
    }
}

void RoomDecomposer::freeRoomId() {
    if (!roomId) return;
    for (int r = 0; r < lastR; r++) delete[] roomId[r];
    delete[] roomId;
    roomId = nullptr;
    lastR = 0;
}

int RoomDecomposer::getRoomId(int r, int c) const {
    if (!roomId) return -1;
    return roomId[r][c];
}

void RoomDecomposer::floodFillRoom(GridModel& grid, int startR, int startC, int rid, Room& outRoom) {
    ds::Queue<Position> q;
    q.enqueue(Position(startR, startC));
    roomId[startR][startC] = rid;

    while (!q.isEmpty()) {
        Position u = q.dequeue();

        if (grid.isFloor(u.r, u.c)) {
            outRoom.floorCells.pushBack(u);
            outRoom.uncleanedCount++;

            if (u.r < outRoom.rmin) outRoom.rmin = u.r;
            if (u.r > outRoom.rmax) outRoom.rmax = u.r;
            if (u.c < outRoom.cmin) outRoom.cmin = u.c;
            if (u.c > outRoom.cmax) outRoom.cmax = u.c;
        }

        for (int k = 0; k < 4; k++) {
            int nr = u.r + DR[k];
            int nc = u.c + DC[k];
            if (!grid.inBounds(nr, nc)) continue;

            if (grid.isDoor(nr, nc)) continue;

            if (!grid.isFloor(nr, nc) && !grid.isDock(nr, nc)) continue;

            if (roomId[nr][nc] != -1) continue;
            roomId[nr][nc] = rid;
            q.enqueue(Position(nr, nc));
        }
    }
}

int RoomDecomposer::assignRooms(GridModel& grid, ds::LinkedList<Room>& rooms) {
    rooms.clear();
    roomCount = 0;

    allocRoomId(grid.R(), grid.C());

    for (int r = 0; r < grid.R(); r++) {
        for (int c = 0; c < grid.C(); c++) {
            if ((!grid.isFloor(r,c) && !grid.isDock(r,c)) || roomId[r][c] != -1) continue;

            Room room;
            room.id = roomCount;

            floodFillRoom(grid, r, c, roomCount, room);

            rooms.pushBack(room);
            roomCount++;
        }
    }
    return roomCount;
}
