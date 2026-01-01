#ifndef GRID_MODEL_HPP
#define GRID_MODEL_HPP
#include <vector>
#include "core/Position.hpp"
#include <string>

enum class CellType {
    WALL,       
    CLEAN,      
    DIRTY,      
    DOCK,
    DOOR,
    CLEANED,     
    UNDEFINED   
};


class GridModel {
public:
    int rows = 0;
    int cols = 0;
    int initialBattery = 100;
    std::vector<std::vector<CellType>> cells;
    int R() const {
        return rows;
    }
    int C()const{
        return cols;
    }
    bool inBounds(int r, int c) const{
        return r >= 0 && r < rows && c >= 0 && c < cols;
    }
    bool isFloor(int r, int c) const{
        if(inBounds(r,c) == false){
            return false;
        }
        auto t = cells[r][c];
        return t == CellType::CLEAN || t == CellType::CLEANED; 
    }
    bool isCleaned(int r, int c) const{
        return inBounds(r,c) && cells[r][c] == CellType::CLEANED;
    }
    bool isDock(int r, int c) const{
        return inBounds(r, c) && cells[r][c] == CellType::DOCK;
    }
    bool isDoor(int r, int c) const{
        return inBounds(r, c) && cells[r][c] == CellType::DOOR;
    }
    bool isWall(int r, int c) const{
        return inBounds(r, c) && cells[r][c] == CellType::WALL;
    }
    void markCleaned(int r, int c){
        if(inBounds(r,c) && cells[r][c] == CellType::CLEAN){
            cells[r][c] = CellType::CLEANED;
        }
    }
    
    
    Position dockPosition;
    
    GridModel() : rows(0), cols(0), initialBattery(100) {}
};

#endif