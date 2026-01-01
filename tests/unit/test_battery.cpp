#include <cassert>
#include <iostream>
#include "core/BatteryManager.hpp"
#include "core/GridModel.hpp"
#include "core/PathFinder.hpp"
#include "../tests/unit/TestUtil.hpp"

void test_battery(){
    std::cout << "test/unit/ [Battery Manager]" << std::endl;
    Test test;
    GridModel grid;
    grid.rows = 1;
    grid.cols = 3;
    grid.cells = {{ CellType::DOCK, CellType::CLEAN, CellType::CLEAN }};
    grid.dockPosition = Position(0,0);
    PathFinder pf(grid);
    BatteryManager bm(10, pf);
    test.check(bm.getBattery() == 10, "initial battery is cap");
    test.check(bm.getState() == BatteryState::CLEANING, "initial state clean");
    bm.consume(9);
    test.check(bm.getBattery() == 1, "consume reduces battery");
    bool mustReturn = bm.needsReturn(Position(0,2));
    test.check(mustReturn == true, "needs to return - true when cannot reach dock");
    test.check(bm.getState() == BatteryState::RETURNING, "state becomes return when needs to return true");

    bm.recharge();
    test.check(bm.getBattery() == 10, "recharge restores to cap");
    test.check(bm.getState() == BatteryState::CLEANING, "state becomes clean after recharge");

    test.summary();

}