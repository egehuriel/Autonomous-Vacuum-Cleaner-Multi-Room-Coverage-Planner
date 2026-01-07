#ifndef GRID_PARSER_HPP
#define GRID_PARSER_HPP

#include <fstream>
#include <vector>
#include <stdexcept>
#include "libraries/json.hpp"
#include "core/GridModel.hpp"

using json = nlohmann::json;

class GridParser {
public:
    static GridModel parse(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open())
            throw std::runtime_error("File could not be opened");

        json data;
        file >> data;

        GridModel model;
        model.initialBattery = data.value("battery", 100);

        json gridJson = data["grid"];
        if (!gridJson.is_array() || gridJson.empty())
            throw std::runtime_error("Invalid grid");

        int dockCount = 0;


        if (gridJson[0].is_string()) {
            std::vector<std::string> gridStr = gridJson;

            model.rows = gridStr.size();
            model.cols = gridStr[0].size();
            model.cells.resize(model.rows, std::vector<CellType>(model.cols));

            for (int r = 0; r < model.rows; r++) {
                if ((int)gridStr[r].size() != model.cols)
                    throw std::runtime_error("Grid is not rectangular");

                for (int c = 0; c < model.cols; c++) {
                    char ch = gridStr[r][c];

                    if (ch == 'W') model.cells[r][c] = CellType::WALL;
                    else if (ch == 'C') model.cells[r][c] = CellType::DIRTY;
                    else if (ch == 'S') model.cells[r][c] = CellType::CLEAN;
                    else if (ch == 'D') {
                        model.cells[r][c] = CellType::DOCK;
                        model.dockPosition = {r, c};
                        dockCount++;
                    } else {
                        throw std::runtime_error("Invalid character in grid");
                    }
                }
            }
        }

        else {
            model.rows = gridJson.size();
            model.cols = gridJson[0].size();
            model.cells.resize(model.rows, std::vector<CellType>(model.cols));

            for (int r = 0; r < model.rows; r++) {
                if ((int)gridJson[r].size() != model.cols)
                    throw std::runtime_error("Grid is not rectangular");

                for (int c = 0; c < model.cols; c++) {
                    std::string cell = gridJson[r][c];

                    if (cell == "W") model.cells[r][c] = CellType::WALL;
                    else if (cell == "C") model.cells[r][c] = CellType::DIRTY;
                    else if (cell == "S") model.cells[r][c] = CellType::CLEAN;
                    else if (cell == "D") {
                        model.cells[r][c] = CellType::DOCK;
                        model.dockPosition = {r, c};
                        dockCount++;
                    } else {
                        throw std::runtime_error("Invalid cell value");
                    }
                }
            }
        }

        if (dockCount != 1)
            throw std::runtime_error("Exactly one Dock is required");

        return model;
    }
};

#endif

