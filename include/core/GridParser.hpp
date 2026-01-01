#ifndef GRID_PARSER_HPP
#define GRID_PARSER_HPP

#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept> 
#include "libraries/json.hpp"
#include "core/GridModel.hpp"

using json = nlohmann::json;

class GridParser {
public:
    static GridModel parse(const std::string& filename) {
        std::ifstream file(filename);
        GridModel model;

        if (!file.is_open()) {
            throw std::runtime_error("Dosya acilamadi: " + filename);
        }

        json data;
        file >> data;

        model.initialBattery = data.value("battery", 100);
        std::vector<std::string> gridStr = data["grid"];
        
        if (gridStr.empty()) throw std::runtime_error("Grid bos olamaz!");

        model.rows = gridStr.size();
        model.cols = gridStr[0].size();
        int dockCount = 0;

        model.cells.resize(model.rows, std::vector<CellType>(model.cols));

        for (int r = 0; r < model.rows; ++r) {
            
            if (gridStr[r].size() != (size_t)model.cols) {
                throw std::runtime_error("Hata: Grid dikdortgen degil!");
            }

            for (int c = 0; c < model.cols; ++c) {
                char ch = gridStr[r][c];
                if (ch == 'W') {
                    model.cells[r][c] = CellType::WALL;
                } else if (ch == 'D') {
                    model.cells[r][c] = CellType::DOCK;
                    model.dockPosition = Position(r,c);
                    dockCount++;
                } else if (ch == 'C') {
                    model.cells[r][c] = CellType::DIRTY;
                } else if (ch == 'S') { 
                    model.cells[r][c] = CellType::CLEAN;
                } else {
                    
                    throw std::runtime_error("Hata: Gecersiz karakter: " + std::string(1, ch));
                }
            }
        }

        
        if (dockCount != 1) {
            throw std::runtime_error("Hata: Haritada tam olarak 1 adet Dock (D) olmalidir!");
        }

        return model;
    }
};

#endif