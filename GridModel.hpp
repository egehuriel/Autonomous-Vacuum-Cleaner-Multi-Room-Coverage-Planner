#ifndef GRID_MODEL_HPP
#define GRID_MODEL_HPP

#include <vector>
#include <string>

enum class CellType {
    WALL,       
    CLEAN,      
    DIRTY,      
    DOCK,     
    UNDEFINED   
};


struct Position {
    int x, y;
};


class GridModel {
public:
    int rows;
    int cols;
    
    
    std::vector<std::vector<CellType>> cells;
    
    
    Position dockPosition;

    
    int initialBattery;

    
    GridModel() : rows(0), cols(0), initialBattery(100) {}
};

#endif