#pragma once

#include "core/PathFinder.hpp"

enum class BatteryState {
    CLEANING,
    RETURNING,
    CHARGING
};

class BatteryManager {
private:
    int battery;
    int capacity;
    BatteryState state;
    PathFinder& pathFinder;

public:
    BatteryManager(int cap, PathFinder& pf);

    void consume(int amount);
    bool needsReturn(Position pos);
    void recharge();

    int getBattery() const;
    BatteryState getState() const;
};
