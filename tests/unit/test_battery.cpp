#include <cassert>
#include <iostream>
#include "core/BatteryManager.hpp"
#include "core/GridModel.hpp"
#include "core/PathFinder.hpp"

void test_battery(){
    std::cout << "test/unit/ [Battery Manager]" << std::endl;
    GridModel gridmodel;
    gridmodel.rows = 1;
    gridmodel.cols = 3;
    gridmodel.cells = {{ CellType::DOCK, CellType::CLEAN, CellType::CLEAN }};
    gridmodel.dockPosition = {0, 0};

    PathFinder pathfinder(gridmodel);
    BatteryManager batterymanager(10, pathfinder);
    assert(batterymanager.getBattery() == 10);
    assert(batterymanager.getState() == BatteryState::CLEANING);
    batterymanager.consume(9);
    assert(batterymanager.getBattery() == 1);

    bool robotreturn = batterymanager.needsReturn({0, 2});
    assert(robotreturn == true);
    assert(batterymanager.getState() == BatteryState::RETURNING);

    std::cout << "-------PASSED-------" << std::endl << std::endl;

}