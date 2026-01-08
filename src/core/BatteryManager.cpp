#include "core/BatteryManager.hpp"

BatteryManager::BatteryManager(int cap, PathFinder& pf, int margin)
    : battery(cap), capacity(cap), state(BatteryState::CLEANING), safetyMargin(margin), pathFinder(pf) {}

void BatteryManager::consume(int amount) {
    if(amount <= 0){
        return;
    }
    battery = battery - amount;
    if (battery < 0)
        battery = 0;
}

bool BatteryManager::needsReturn(Position pos) {
    int dist = pathFinder.distanceToDock(pos);
    if(dist < 0){
        state = BatteryState::RETURNING;
        return true;
    }
    if (battery < dist + safetyMargin){
        state = BatteryState::RETURNING;
        return true;
    }
    state = BatteryState::CLEANING;
    return false;
}
void BatteryManager::recharge() {
    state = BatteryState::CHARGING;
    battery = capacity;
    state = BatteryState::CLEANING;
}
int BatteryManager::getBattery() const {
    return battery;
}

BatteryState BatteryManager::getState() const {
    return state;
}

