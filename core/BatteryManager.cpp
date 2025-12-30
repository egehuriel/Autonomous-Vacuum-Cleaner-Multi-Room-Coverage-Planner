#include "BatteryManager.hpp"

BatteryManager::BatteryManager(int cap, PathFinder& pf)
    : capacity(cap), battery(cap), state(CLEANING), pathFinder(pf) {}

void BatteryManager::consume(int amount) {
    battery = battery - amount;
    if (battery < 0)
        battery = 0;
}

bool BatteryManager::needsReturn(Position pos) {
    if (!pathFinder.canReachDock(pos, battery)) {
        state = RETURNING;
        return true;
    }
    return false;
}
void BatteryManager::recharge() {
    battery = capacity;
    state = CLEANING;
}
int BatteryManager::getBattery() const {
    return battery;
}

BatteryState BatteryManager::getState() const {
    return state;
}

