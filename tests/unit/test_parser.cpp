#include <cassert>
#include <iostream>
#include <string>
#include "core/GridParser.hpp"
#include "core/GridModel.hpp"

void test_parser(){
    std::cout << "test/unit/ [PARSER]" << std::endl;
    const std::string pass1 = "data/small_room.json";
    const std::string pass2 = "data/obstacle_heavy.json";
    const std::string fail1 = "data/invalid_grid.json"; 

    auto grid1 = GridParser::parse(pass1);
    auto grid2 = GridParser::parse(pass2);

    bool failexcept = false;
    try{
        auto gridfail = GridParser::parse(fail1);
        (void) gridfail;
    }catch(std::runtime_error& error){
        failexcept = true;
    }
    assert(failexcept && "data/invalid_grid.json exception");
    std::cout << "-------PASSED-------" << std::endl << std::endl;


}