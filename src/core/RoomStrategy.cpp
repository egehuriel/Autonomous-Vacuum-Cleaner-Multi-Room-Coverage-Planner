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
    for (int i = 0; i < n; i++) arr[i] = rooms.get(i);

    for (int i = 0; i < n; i++) {
        int best = 1000000000;
        int m = (int)arr[i].floorCells.getSize();

        for (int k = 0; k < m; k++) {
            Position p = arr[i].floorCells.get(k);
            int d = distFunc(p);
            if (d < best) best = d;
        }

        arr[i].minDockDist = (best == 1000000000 ? 100000000 : best);
    }

    selectionSortByMinDockDist(arr, n);

    for (int i = 0; i < n; i++) order.pushBack(arr[i].id);

    delete[] arr;
    return order;
}
