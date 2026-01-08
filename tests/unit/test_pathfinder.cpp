#include <iostream>
#include "core/GridModel.hpp"
#include "core/PathFinder.hpp"
#include "../tests/unit/TestUtil.hpp"

static GridModel makeGrid_1x3_open() {
    GridModel g;
    g.allocate(1, 3, CellType::WALL);
    g.at(0,0) = CellType::DOCK;
    g.at(0,1) = CellType::FLOOR;
    g.at(0,2) = CellType::FLOOR;
    g.dockPosition = Position(0,0);
    g.startPosition = Position(0,0);
    return g;
}

static GridModel makeGrid_1x3_blocked() {
    GridModel g;
    g.allocate(1, 3, CellType::WALL);

    g.at(0,0) = CellType::DOCK;
    g.at(0,1) = CellType::WALL;
    g.at(0,2) = CellType::FLOOR;
    g.dockPosition = Position(0,0);
    g.startPosition = Position(0,0);
    return g;
}

void test_pathfinder() {
    std::cout << "test/unit/ [Path Finder]" << std::endl;
    Test test;

    {
        GridModel g = makeGrid_1x3_open();
        PathFinder pf(g);
        test.check(pf.distanceToDock(Position(0,0)) == 0, "dock distance 0");
        test.check(pf.distanceToDock(Position(0,2)) == 2, "end distance 2");
        test.check(pf.canReachDock(Position(0,2), 2) == true, "battery 2 ok");
        test.check(pf.canReachDock(Position(0,2), 1) == false, "battery 1 not ok");
    }

    {
        GridModel g = makeGrid_1x3_blocked();
        PathFinder pf(g);
        test.check(pf.distanceToDock(Position(0,2)) == -1, "blocked distance -1");
        test.check(pf.canReachDock(Position(0,2), 999) == false, "blocked can reach false");
    }

    test.summary();
}