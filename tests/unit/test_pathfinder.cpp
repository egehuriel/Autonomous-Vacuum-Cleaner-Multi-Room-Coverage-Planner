#include <cassert>
#include <iostream>
#include "core/GridModel.hpp"
#include "core/PathFinder.hpp"
#include "../tests/unit/TestUtil.hpp"

void test_pathfinder(){
    std::cout << "test/unit/ [Path Finder]" << std::endl;
    Test test;
    //test 1 - 1x3 hall Dc
    {
        GridModel gridmodel;
        gridmodel.rows = 1;
        gridmodel.cols = 3;
        gridmodel.cells = {{ CellType::DOCK, CellType::CLEAN, CellType::CLEAN}};
        gridmodel.dockPosition = Position(0,0);
        PathFinder pathfinder(gridmodel);
        test.check(pathfinder.distanceToDock(Position(0,0)) == 0, "distance to charge == 0");
        test.check(pathfinder.distanceToDock(Position(0,2)) == 2, "distance to end == 2" );
        test.check(pathfinder.canReachDock(Position(0,2), 2) == true, "can reach with battery = 2 is true" );
        test.check(pathfinder.canReachDock(Position(0,2), 1) == false, "can reach with battery = 1 is false");
    }
    //test 2 - 1x3 D W
    {
        GridModel gridmodel;
        gridmodel.rows = 1;
        gridmodel.cols = 3;
        gridmodel.cells = {{ CellType::DOCK, CellType::WALL, CellType::CLEAN}};
        gridmodel.dockPosition = Position(0,0);
        PathFinder pathfinder(gridmodel);
        test.check(pathfinder.distanceToDock(Position(0,2)) == -1, "distance unreachable = -1");
        test.check(pathfinder.canReachDock(Position(0,2), 1) == false, "can reach false if unreacheble");
    }
    //test 3 - 3x3 DW W detour
    {
        GridModel gridmodel;
        gridmodel.rows = 3;
        gridmodel.cols = 3;
        gridmodel.cells = {
            { CellType::DOCK, CellType::WALL, CellType::CLEAN },
            { CellType::CLEAN, CellType::WALL, CellType::CLEAN },
            { CellType::CLEAN, CellType::CLEAN, CellType::CLEAN }
        };
        gridmodel.dockPosition = Position(0,0);
        PathFinder pathfinder(gridmodel);
        test.check(pathfinder.distanceToDock(Position(0,2)) == 6, "distance with detour = 6");
        test.check(pathfinder.canReachDock(Position(0,2), 6) == true, "can reach with battery at = 6 true");
        test.check(pathfinder.canReachDock(Position(0,2), 5) == false, "can reach with battery at = 5 false");
    }
    test.summary();
}