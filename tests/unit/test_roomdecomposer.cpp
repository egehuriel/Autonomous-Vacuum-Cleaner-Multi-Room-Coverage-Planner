#include <iostream>
#include "core/RoomDecomposer.hpp"
#include "../tests/unit/TestUtil.hpp"

void test_roomdecomposer(){
    std::cout << "test/unit/ [Room Decomposer]" << std::endl;
    Test test;
    RoomDecomposer decomposer;
    test.check(true, "room decomposer default construct");
    test.summary();
}