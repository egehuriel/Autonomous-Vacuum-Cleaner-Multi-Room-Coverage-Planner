#include <iostream>
#include "core/BatteryManager.hpp"
#include "core/GridModel.hpp"
#include "core/PathFinder.hpp"
#include "../tests/unit/TestUtil.hpp"

static GridModel makeHall_1x3() {
    GridModel g;
    g.allocate(1, 3, CellType::WALL);
    g.at(0,0) = CellType::DOCK;
    g.at(0,1) = CellType::FLOOR;
    g.at(0,2) = CellType::FLOOR;
    g.dockPosition = Position(0,0);
    g.startPosition = Position(0,0);
    return g;
}

static GridModel makeUnreachable_1x3() {
    GridModel g;
    g.allocate(1, 3, CellType::WALL);
    g.at(0,0) = CellType::DOCK;
    g.at(0,1) = CellType::WALL;
    g.at(0,2) = CellType::FLOOR;
    g.dockPosition = Position(0,0);
    g.startPosition = Position(0,0);
    return g;
}

void test_battery() {
    std::cout << "test/unit/ [Battery Manager]" << std::endl;
    Test test;

    // case1 reachable corridor
    {
        GridModel grid = makeHall_1x3();
        PathFinder pf(grid);
        BatteryManager bm(10, pf, 2);

        test.check(bm.getBattery() == 10, "initial battery = capacity");
        test.check(bm.getState() == BatteryState::CLEANING, "initial state CLEANING");
        bm.consume(6);
        bool r1 = bm.needsReturn(Position(0,2));
        test.check(r1 == false, "needsReturn false when battery == dist arti safety margin");
        test.check(bm.getState() == BatteryState::CLEANING, "state stays CLEANING");
        // battery=3: should need return
        bm.consume(1);
        bool r2 = bm.needsReturn(Position(0,2));
        test.check(r2 == true, "needsReturn true when battery < dist+margin");
        test.check(bm.getState() == BatteryState::RETURNING, "state becomes RETURNING");
        bm.recharge();
        test.check(bm.getBattery() == 10, "recharge restores battery to capacity");
        test.check(bm.getState() == BatteryState::CLEANING, "state becomes CLEANING after recharge");
    }
    //case 2
    {
        GridModel grid = makeUnreachable_1x3();
        PathFinder pf(grid);
        BatteryManager bm(100, pf, 2);
        bool r = bm.needsReturn(Position(0,2));
        test.check(r == true, "need return - true when dock unreachable");
        test.check(bm.getState() == BatteryState::RETURNING, "state RETURNING when unreachable");
    }

    test.summary();
}