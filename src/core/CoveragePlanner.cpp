#include "core/CoveragePlanner.hpp"
#include "core/RoomDecomposer.hpp"
#include <utility>

static void clearStack(ds::Stack<Position>& st) {
    while (!st.isEmpty()) st.pop();
}

static int stackLen(ds::Stack<Position>& st){
    int len = 0;
    ds::Stack<Position> temp1;
    ds::Stack<Position> temp2;
    while(!st.isEmpty()){
        Position p = st.pop();
        len++;
        temp1.push(std::move(p));
    }
    while(!temp1.isEmpty()){
        temp2.push(temp1.pop());
    }
    while(!temp2.isEmpty()){
        st.push(temp2.pop());
    }
    return len;
}

static void copyStack(ds::Stack<Position>& dst, ds::Stack<Position>& src) {
    ds::Stack<Position> tmp1;
    ds::Stack<Position> tmp2;
    clearStack(dst);

    while (!src.isEmpty()) {
        Position x = src.pop();
        tmp1.push(std::move(x));
    }

    while (!tmp1.isEmpty()) {
        tmp2.push(tmp1.pop());
    }
    while(!tmp2.isEmpty()){
        Position x = tmp2.pop();
        src.push(Position(x.r, x.c));
        dst.push(std::move(x));
    }
}

CoveragePlanner::CoveragePlanner()
    : grid(nullptr), rooms(nullptr), decomposer(nullptr),
      stuckCounter(0), lastCleanedTotal(0), roomOrderIndex(0) {}

void CoveragePlanner::init(GridModel* g, ds::LinkedList<Room>* rms, RoomDecomposer* dec, const Hooks& h) {
    grid = g;
    rooms = rms;
    decomposer = dec;
    hooks = h;

    stuckCounter = 0;
    lastCleanedTotal = countCleanedTotal();
    roomOrderIndex = 0;
    roomOrder.clear();
}

void CoveragePlanner::setRoomOrder(const ds::LinkedList<int>& order) {
    roomOrder.clear();
    for (int i = 0; i < (int)order.size(); i++){
        roomOrder.pushBack(order.getAt(i));
    }
    roomOrderIndex = 0;
}

int CoveragePlanner::countCleanedTotal() const {
    int cnt = 0;
    for (int r = 0; r < grid->R(); r++)
        for (int c = 0; c < grid->C(); c++)
            if (grid->isFloor(r,c) && grid->isCleaned(r,c)) cnt++;
    return cnt;
}

bool CoveragePlanner::allFloorsCleaned() const {
    for (int r = 0; r < grid->R(); r++)
        for (int c = 0; c < grid->C(); c++)
            if (grid->isFloor(r,c) && !grid->isCleaned(r,c)) return false;
    return true;
}

bool CoveragePlanner::roomHasUncleaned(int roomId) const {
    for (int i = 0; i < (int)rooms->size(); i++) {
        Room rm = rooms->getAt(i);
        if (rm.id != roomId) continue;

        int m = (int)rm.floorCells.size();
        for (int k = 0; k < m; k++) {
            Position p = rm.floorCells.getAt(k);
            if (!grid->isCleaned(p.r, p.c)) return true;
        }
        return false;
    }
    return false;
}

void CoveragePlanner::buildSweepTargetsForRoom(int roomId, ds::LinkedList<Position>& outTargets) const {
    outTargets.clear();

    Room rm;
    bool found = false;
    for (int i = 0; i < (int)rooms->size(); i++) {
        Room tmp = rooms->getAt(i);
        if (tmp.id == roomId) { rm = tmp; found = true; break; }
    }
    if (!found || rm.rmax < 0) return;

    bool leftToRight = true;
    for (int r = rm.rmin; r <= rm.rmax; r++) {
        if (leftToRight) {
            for (int c = rm.cmin; c <= rm.cmax; c++) {
                if (grid->isFloor(r,c) && decomposer->getRoomId(r,c) == roomId)
                    outTargets.pushBack(Position(r,c));
            }
        } else {
            for (int c = rm.cmax; c >= rm.cmin; c--) {
                if (grid->isFloor(r,c) && decomposer->getRoomId(r,c) == roomId)
                    outTargets.pushBack(Position(r,c));
            }
        }
        leftToRight = !leftToRight;
    }
}

bool CoveragePlanner::pickNearestUncleaned(Position& outTarget) const {
    for (int r = 0; r < grid->R(); r++) {
        for (int c = 0; c < grid->C(); c++) {
            if (grid->isFloor(r,c) && !grid->isCleaned(r,c)) {
                outTarget = Position(r,c);
                return true;
            }
        }
    }
    return false;
}

bool CoveragePlanner::pickNextTarget(Position& outTarget) {
    while (roomOrderIndex < (int)roomOrder.size()) {
        int rid = roomOrder.getAt(roomOrderIndex);
        if (roomHasUncleaned(rid)) {
            ds::LinkedList<Position> sweep;
            buildSweepTargetsForRoom(rid, sweep);

            for (int i = 0; i < (int)sweep.size(); i++) {
                Position p = sweep.getAt(i);
                if (!grid->isCleaned(p.r, p.c)) {
                    outTarget = p;
                    return true;
                }
            }
        }
        roomOrderIndex++;
    }

   
    return pickNearestUncleaned(outTarget);
}

bool CoveragePlanner::planNextPath(const Position& currentPos, int battery, ds::Stack<Position>& outPath) {
    clearStack(outPath);
    if (allFloorsCleaned()) return false;
    if (!hooks.buildPath || !hooks.distToDock) return false;

    Position target;
    if (!pickNextTarget(target)) return false;

    ds::Stack<Position> path;
    bool ok = hooks.buildPath(currentPos, target, path);
    int lennodes = stackLen(path);
    if (!ok || lennodes == 0) {
        if (hooks.requestReturnToDock) hooks.requestReturnToDock();
        if(hooks.buildPath && grid){
            bool okdock = hooks.buildPath(currentPos, grid -> dockPosition, outPath);
            return okdock;
        }
        return false;
    }

    int pathLen = lennodes - 1;
    int back = hooks.distToDock(target);
    int margin = hooks.safetyMargin;

    if(back < 0 || pathLen + back + margin > battery){
        if(hooks.requestReturnToDock){
            hooks.requestReturnToDock();
        }
        bool okdock = hooks.buildPath(currentPos, grid -> dockPosition, outPath);
        return okdock;
    }

    copyStack(outPath, path);
    return true;
}