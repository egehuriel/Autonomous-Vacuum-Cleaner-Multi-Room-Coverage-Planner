#pragma once
#include "core/GridModel.hpp"
#include "core/Room.hpp"
#include "core/Position.hpp"
#include "data_structures/LinkedList.h"
#include "data_structures/Stack.h"
#include "core/RoomDecomposer.hpp"

class CoveragePlanner {
public:
    typedef bool (*BuildPathFunc)(const Position& from, const Position& to, ds::Stack<Position>& outPath);
    typedef int  (*DistToDockFunc)(const Position& pos);
    typedef void (*RequestReturnDockFunc)();

    struct Hooks {
        BuildPathFunc buildPath = nullptr;
        DistToDockFunc distToDock = nullptr;
        RequestReturnDockFunc requestReturnToDock = nullptr;
        int safetyMargin = 2;
    };

    CoveragePlanner();

    void init(GridModel* g, ds::LinkedList<Room>* rms, RoomDecomposer* dec, const Hooks& hooks);

    bool planNextPath(const Position& currentPos, int battery, ds::Stack<Position>& outPath);

    bool allFloorsCleaned() const;

private:
    GridModel* grid;    
    ds::LinkedList<Room>* rooms;
    RoomDecomposer* decomposer;
    Hooks hooks;
    
    int stuckCounter;
    int lastCleanedTotal;
    ds::LinkedList<int> roomOrder;   
    int roomOrderIndex;

    int countCleanedTotal() const;
    int findCurrentRoomId(const Position& p) const;
    bool roomHasUncleaned(int roomId) const;

    bool pickNextTarget(Position& outTarget);

    void buildSweepTargetsForRoom(int roomId, ds::LinkedList<Position>& outTargets) const;

    bool pickNearestUncleaned(Position& outTarget) const;
public:
    void setRoomOrder(const ds::LinkedList<int>& order);

};
