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
        GridModel model;
        if (!file.is_open()) {
            throw std::runtime_error("Dosya acilamadi: " + filename);
        }
        json data;
        try {
            file >> data;
        } catch (const json::parse_error& e) {
            throw std::runtime_error("JSON format hatasi: " + std::string(e.what()));
        }
        // battery ve start position
        if (data.contains("vacuum") && data["vacuum"].is_object()) {
            const json& v = data["vacuum"];
            model.initialBattery = v.value("battery_capacity", v.value("battery", 100));
            if (v.contains("start_position") &&
                v["start_position"].is_array() &&
                v["start_position"].size() == 2 &&
                v["start_position"][0].is_number_integer() &&
                v["start_position"][1].is_number_integer()) {        
                model.startPosition = Position(
                    v["start_position"][0].get<int>(),
                    v["start_position"][1].get<int>()
                );
            }
        } else {
            model.initialBattery = data.value("battery", 100);
        }
        //grid parsing
        if(!data.contains("grid")){
            throw std::runtime_error("Hata: json icinde grid bulunamadi");
        }    
        int dockCount = 0;
        const json& g = data["grid"];
        if(g.is_array() && !g.empty() && g[0].is_array()){
            model.rows = (int)g.size();
            model.cols = (int)g[0].size();
            if(model.rows <= 0 || model.cols <= 0){
                throw std::runtime_error("Grid boyutlari hatali (bos)!");
            }
            model.allocate(model.rows, model.cols, CellType::WALL);
            for (int i = 0; i < model.rows; ++i) {
                if (!g[i].is_array() || (int)g[i].size() != model.cols) {
                    throw std::runtime_error("Hata: grid dikdortgen degil (satir uzunluklari esit degil)");
                }
                for(int j = 0; j < model.cols; ++j){
                    if(!g[i][j].is_string()){
                        throw std::runtime_error("hata grid tipi string olmali");
                    }  
                    std::string token = g[i][j].get<std::string>();                          
                    if(token.size() != 1){
                        throw std::runtime_error("hata gecersiz token " + token);
                    }
                    char ch = token[0];
                    switch (ch) {
                        case 'W':
                            model.at(i, j) = CellType::WALL;
                            break;
                        case 'F':
                            model.at(i, j) = CellType::FLOOR;
                            break;
                        case 'O':
                            model.at(i, j) = CellType::OBSTACLE;
                            break;
                        case 'D':
                            model.at(i, j) = CellType::DOOR;
                            break;
                        case 'C':
                            model.at(i, j) = CellType::DOCK;
                            model.dockPosition = Position(i, j);
                            dockCount++;
                            break;
                        default:
                            throw std::runtime_error("Hata: gecersiz karakter: " + std::string(1, ch));
                    }
                }
            }
        } else {
            throw std::runtime_error("Hata: grid formati desteklenmiyor (2d array bekleniyor)");
        }
        if(dockCount != 1){
            throw std::runtime_error("Hata: Haritada tam olarak 1 adet charging dock (C) olmalidir");
        }
        if (!model.inBounds(model.startPosition.r, model.startPosition.c)) {
            model.startPosition = model.dockPosition;
        }
        return model;
    }
};

#endif

