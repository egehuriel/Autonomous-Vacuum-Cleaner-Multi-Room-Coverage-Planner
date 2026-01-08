#pragma once
#include "core/GridModel.hpp"
#include "core/Room.hpp"
#include "core/Position.hpp"
#include "data_structures/LinkedList.h"
#include "data_structures/Stack.h"
#include "core/RoomDecomposer.hpp"
#include <functional>

class CoveragePlanner {
public:
    using BuildPathFunc = std::function<bool(const Position&, const Position&, ds::Stack<Position>&)>;
    using DistToDockFunc = std::function<int(const Position&)>;
    using RequestReturnDockFunc = std::function<void()>;

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
    int countCleanedTotal() const;
    void setRoomOrder(const ds::LinkedList<int>& order);

private:
    GridModel* grid;    
    ds::LinkedList<Room>* rooms;
    RoomDecomposer* decomposer;
    Hooks hooks;
    int stuckCounter;
    int lastCleanedTotal;
    ds::LinkedList<int> roomOrder;   
    int roomOrderIndex;
    int findCurrentRoomId(const Position& p) const;
    bool roomHasUncleaned(int roomId) const;
    bool pickNextTarget(Position& outTarget);
    void buildSweepTargetsForRoom(int roomId, ds::LinkedList<Position>& outTargets) const;
    bool pickNearestUncleaned(Position& outTarget) const;
};