#pragma once
#include <vector>
#include <stdexcept>
#include <utility>
#include "core/Position.hpp"

enum class CellType {
    WALL,
    FLOOR,
    OBSTACLE,
    DOOR,
    DOCK,
    CLEANED
};

struct GridModel {
    int rows = 0;
    int cols = 0;
    int initialBattery = 100;
    Position startPosition;
    CellType* cells = nullptr;
    Position dockPosition;

    GridModel() = default;

    // Rule of Five: Destructor
    ~GridModel() {
        release();
    }
    
    // Rule of Five: Copy Constructor
    GridModel(const GridModel& other) {
        copyFrom(other);
    }

    // Rule of Five: Copy Assignment
    GridModel& operator=(const GridModel& other){
        if(this != &other){
            release();
            copyFrom(other);
        }
        return *this;
    }

    // Rule of Five: Move Constructor
    GridModel(GridModel&& other) noexcept {
        moveFrom(std::move(other));
    }

    // Rule of Five: Move Assignment
    GridModel& operator=(GridModel&& other) noexcept {
        if (this != &other) {
            release();
            moveFrom(std::move(other));
        }
        return *this;
    }

    int R() const { return rows; }
    int C() const { return cols; }

    bool inBounds(int r, int c) const {
        return (r >= 0 && r < rows && c >= 0 && c < cols);
    }

    void allocate(int r, int c, CellType fill = CellType::WALL){
        if(r <= 0 || c <= 0){
            throw std::invalid_argument("GridModel::allocate hatali boyut");
        }
        release();
        rows = r;
        cols = c;
        cells = new CellType[rows * cols];
        for(int i = 0; i < rows * cols; i++){
            cells[i] = fill;
        }
    }

    CellType& at(int r, int c){
        if(!inBounds(r,c)){
            throw std::out_of_range("GridModel::at out of bound");
        }
        return cells[r * cols + c];
    }

    const CellType& at(int r, int c) const{
        if(!inBounds(r,c)){
            throw std::out_of_range("GridModel::at out of bound");
        }
        return cells[r * cols + c];
    }

    bool isWall(int r, int c) const {
        return inBounds(r, c) && at(r, c) == CellType::WALL;
    }

    bool isObstacle(int r, int c) const{
        return inBounds(r, c) && at(r, c) == CellType::OBSTACLE;
    }

    bool isFloor(int r, int c) const {
        if (!inBounds(r, c)) return false;
        CellType t = at(r, c);
        return (t == CellType::FLOOR || t == CellType::CLEANED);
    }

    bool isTraversable(int r, int c) const {
        if(!inBounds(r, c)) return false;
        CellType t = at(r, c);
        return (t != CellType::WALL && t != CellType::OBSTACLE);
    }

    bool isDock(int r, int c) const {
        return inBounds(r, c) && at(r, c) == CellType::DOCK;
    }

    bool isDoor(int r, int c) const {
        return inBounds(r, c) && at(r, c) == CellType::DOOR;
    }

    bool isCleaned(int r, int c) const {
        return inBounds(r, c) && at(r, c) == CellType::CLEANED;
    }

    void markCleaned(int r, int c) {
        if (!inBounds(r, c)) throw std::out_of_range("markCleaned out of bounds");
        if (at(r, c) == CellType::FLOOR) {
            at(r, c) = CellType::CLEANED;
        }
    }

private:
    void release(){
        if (cells) {
            delete[] cells;
            cells = nullptr;
        }
        rows = 0;
        cols = 0;
    }

    void copyFrom(const GridModel& other){
        rows = other.rows;
        cols = other.cols;
        initialBattery = other.initialBattery;
        startPosition = other.startPosition;
        dockPosition = other.dockPosition;
        
        if(other.cells && rows > 0 && cols > 0){
            cells = new CellType[rows * cols];
            for(int i = 0; i < rows * cols; ++i){
                cells[i] = other.cells[i];
            }
        } else {
            cells = nullptr;
        }
    }

    void moveFrom(GridModel&& other){
        rows = other.rows;
        cols = other.cols;
        initialBattery = other.initialBattery;
        startPosition = other.startPosition;
        dockPosition = other.dockPosition;
        cells = other.cells;

        other.cells = nullptr;
        other.rows = 0;
        other.cols = 0;
    }
};