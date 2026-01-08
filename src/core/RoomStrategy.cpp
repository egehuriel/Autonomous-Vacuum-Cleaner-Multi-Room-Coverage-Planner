#include <cstddef>
#include "core/RoomStrategy.hpp"

void RoomStrategy::selectionSortByMinDockDist(Room* arr, int n) {
    for (int i = 0; i < n; i++) {
        int best = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].minDockDist < arr[best].minDockDist) best = j;
        }
        if (best != i) {
            Room tmp = arr[i];
            arr[i] = arr[best];
            arr[best] = tmp;
        }
    }
}

ds::LinkedList<int> RoomStrategy::buildRoomOrder(ds::LinkedList<Room>& rooms, DistFunc distFunc) {
    ds::LinkedList<int> order;
    int n = (int)rooms.getSize();
    if (n <= 0 || distFunc == nullptr) return order;
    Room* arr = new Room[n];
    for (int i = 0; i < n; i++) arr[i] = rooms.get((std::size_t)i);
    for (int i = 0; i < n; i++) {
        int best = 1000000000;
        std::size_t m = arr[i].floorCells.getSize();
        for (std::size_t k = 0; k < m; k++) {
            const Position& p = arr[i].floorCells.get(k);
            int d = distFunc(p);
            if (d >= 0 && d < best) best = d;
        }

        arr[i].minDockDist = (best == 1000000000 ? 100000000 : best);
    }

    selectionSortByMinDockDist(arr, n);

    for (int i = 0; i < n; i++) order.pushBack(arr[i].id);

    delete[] arr;
    return order;
}
