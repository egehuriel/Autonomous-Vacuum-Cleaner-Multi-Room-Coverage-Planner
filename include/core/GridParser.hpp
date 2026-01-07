#ifndef GRID_PARSER_HPP
#define GRID_PARSER_HPP

#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept> 
#include "libraries/json.hpp"
#include "GridModel.hpp"

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
        json gridJson = data["grid"];

        if (!gridJson.is_array() || gridJson.empty()) {
            throw std::runtime_error("Grid bos ya da gecersiz!");
        }

       

        int dockCount = 0;

        if (gridJson[0].is_string()) {
    
            std::vector<std::string> gridStr = gridJson;

            model.rows = gridStr.size();
            model.cols = gridStr[0].size();

            model.cells.resize(model.rows, std::vector<CellType>(model.cols));

            for (int r = 0; r < model.rows; ++r) {
                if (gridStr[r].size() != (size_t)model.cols) {
                    throw std::runtime_error("Grid is not a rectangle");
                }

                for (int c = 0; c < model.cols; ++c) {
                    char ch = gridStr[r][c];

                    if (ch == 'W') model.cells[r][c] = CellType::WALL;
                    else if (ch == 'C') model.cells[r][c] = CellType::DIRTY;
                    else if (ch == 'S') model.cells[r][c] = CellType::CLEAN;
                    else if (ch == 'D') {
                        model.cells[r][c] = CellType::DOCK;
                        model.dockPosition = {r, c};
                        dockCount++;
                    } else {
                        throw std::runtime_error("invalid character");
                    }
                }
            }
        }
        else {
            model.rows = gridJson.size();
            model.cols = gridJson[0].size();

            model.cells.resize(model.rows, std::vector<CellType>(model.cols));

            for (int r = 0; r < model.rows; ++r) {
                if ((int)gridJson[r].size() != model.cols) {
                    throw std::runtime_error("Grid is not a rectangle");
                }

                for (int c = 0; c < model.cols; ++c) {
                    std::string cell = gridJson[r][c];

                    if (cell == "W") model.cells[r][c] = CellType::WALL;
                    else if (cell == "C") model.cells[r][c] = CellType::DIRTY;
                    else if (cell == "S") model.cells[r][c] = CellType::CLEAN;
                    else if (cell == "D") {
                        model.cells[r][c] = CellType::DOCK;
                        model.dockPosition = {r, c};
                        dockCount++;
                    } else {
                        throw std::runtime_error("invalid position");
                    }
                }
            }
        }

        if (dockCount != 1) {
        throw std::runtime_error("There should be exactly 1 Dock");
    }

    return model;
    }
};

#endif