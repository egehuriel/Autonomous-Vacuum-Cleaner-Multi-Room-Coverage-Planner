#include "core/BatteryManager.hpp"

BatteryManager::BatteryManager(int cap, PathFinder& pf)
    : battery(cap), capacity(cap), state(BatteryState::CLEANING), pathFinder(pf) {}

void BatteryManager::consume(int amount) {
    battery = battery - amount;
    if (battery < 0)
        battery = 0;
}

bool BatteryManager::needsReturn(Position pos) {
    if (!pathFinder.canReachDock(pos, battery)) {
        state = BatteryState::RETURNING;
        return true;
    }
    return false;
}
void BatteryManager::recharge() {
    battery = capacity;
    state = BatteryState::CLEANING;
}
int BatteryManager::getBattery() const {
    return battery;
}

BatteryState BatteryManager::getState() const {
    return state;
}

