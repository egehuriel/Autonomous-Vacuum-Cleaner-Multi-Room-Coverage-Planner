#include <iostream>
#include "core/CoveragePlanner.hpp"
#include "core/GridModel.hpp"
#include "core/Position.hpp"
#include "data_structures/Stack.h"
#include "../tests/unit/TestUtil.hpp"

static int distanceB(const Position& a, const Position&b){
    int dr = a.r - b.r;
    if(dr < 0){
        dr = -dr;
    }
    int dc = a.c - b.c;
    if(dc < 0){
        dc = -dc;
    }
    return dr + dc;
}

static bool buildpath(const Position& from, const Position& to, ds::Stack<Position>& outpath) {
    while(outpath.isEmpty() == false){
        outpath.pop();
    }
    outpath.push(Position(from)); 
    
    if(!(from == to)){
        outpath.push(Position(to));
    }
    return true;
}
static GridModel* gridP = nullptr;
static int distanceToDockHook(const Position& pos){
    return distanceB(pos, gridP->dockPosition);
}

static bool requestedreturn = false;
static void requestedreturnhooks(){
    requestedreturn = true;
}
void test_coverageplanner(){
    std::cout << "test/unit/ [Coverage Planner]" << std::endl;
    Test test;
    GridModel gridmodel;
    gridmodel.rows = 1;
    gridmodel.cols = 3;
    gridmodel.cells = {{ CellType::DOCK, CellType::CLEAN, CellType::DIRTY }};
    gridmodel.dockPosition = Position(0,0);   
    gridP = &gridmodel;
    requestedreturn = false;    
    CoveragePlanner planner;
    CoveragePlanner::Hooks hooks;
    hooks.buildPath = &buildpath;              
    hooks.distToDock = &distanceToDockHook;    
    hooks.requestReturnToDock = &requestedreturnhooks;
    hooks.safetyMargin = 0;                    
    planner.init(&gridmodel, nullptr, nullptr, hooks);
    ds::Stack<Position> outpath;
    bool ok = planner.planNextPath(Position(0,0), 100, outpath);
    test.check(ok == true, "plannextpath true when dirty cell and battery ok");
    test.check(outpath.isEmpty() == false, "outpath is not empty");
    requestedreturn = false;
    ds::Stack<Position> outpath2;
    bool ok2 = planner.planNextPath(Position(0,0), 0, outpath2);
    test.check(ok2 == false, "plannextpath returns false battery not ok");
    gridmodel.cells = {{ CellType::DOCK, CellType::CLEAN, CellType::CLEAN }};
    test.check(requestedreturn == true, "hooks called when battery low");

    test.summary();
}