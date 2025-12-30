#include <cassert>
#include <iostream>
#include "core/GridModel.hpp"
#include "core/PathFinder.hpp"

void test_pathfinder(){
    std::cout << "test/unit/ [Path Finder]" << std::endl;
    //test 1 - 1x3 hall D
    {
        GridModel gridmodel;
        gridmodel.rows = 1;
        gridmodel.cols = 3;
        gridmodel.cells = {{ CellType::DOCK, CellType::CLEAN, CellType::CLEAN}};
        gridmodel.dockPosition = {0, 0};
        PathFinder pathfinder(gridmodel);
        assert(pathfinder.distanceToDock({0,0}) == 0);
        assert(pathfinder.distanceToDock({0,2}) == 2);
        assert(pathfinder.canReachDock({0,2}, 2) == true);
        assert(pathfinder.canReachDock({0,2}, 1) == false);
    }
    //test 2 - 1x3 D W
    {
        GridModel gridmodel;
        gridmodel.rows = 1;
        gridmodel.cols = 3;
        gridmodel.cells = {{ CellType::DOCK, CellType::WALL, CellType::CLEAN}};
        gridmodel.dockPosition = {0, 0};
        PathFinder pathfinder(gridmodel);
        assert(pathfinder.distanceToDock({0,2}) == -1);
        assert(pathfinder.canReachDock({0,2}, 999) == false);
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
        gridmodel.dockPosition = {0,0};
        PathFinder pathfinder(gridmodel);
        assert(pathfinder.distanceToDock({0,2}) == 6);
        assert(pathfinder.canReachDock({0,2}, 6) == true);
        assert(pathfinder.canReachDock({0,2} , 5) == false);
    }
    std::cout << "-------PASSED-------" << std::endl << std::endl;
}