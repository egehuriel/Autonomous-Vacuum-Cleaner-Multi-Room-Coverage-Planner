#include <cassert>
#include <iostream>
#include <string>
#include "core/GridParser.hpp"
#include "core/GridModel.hpp"
#include "../tests/unit/TestUtil.hpp"

void test_parser(){
    std::cout << "test/unit/ [PARSER]" << std::endl;
    Test test;

    const std::string ok1 = "data/small_room.json";
    const std::string ok2 = "data/obstacle_heavy.json";
    const std::string invalid = "data/invalid_grid.json";
    {
        bool ok = true;
        try{
            (void)GridParser::parse(ok1);
        }catch(const std::exception& error){
            ok = false;
        }
        test.check(ok == true, "smallroom parse works");
    }
    {
        bool ok = true;
        try{
            (void)GridParser::parse(ok2);            
        }catch(const std::exception& error){
            ok = false;
        }
        test.check(ok == true, "obstacleheavy parse works");
    }
    {
    bool throws = exceptionthrows([&](){
        (void)GridParser::parse(invalid);
    });
        test.check(throws == true, "invalid grid exception handled");
    }
    test.summary();

}