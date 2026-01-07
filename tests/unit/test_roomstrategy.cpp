#include <iostream>
#include "core/RoomStrategy.hpp"
#include "../tests/unit/TestUtil.hpp"

void test_roomstrategy(){
    std::cout << "test/unit/ [Room Strategy]" << std::endl;
    Test test;

    RoomStrategy strategy;
    test.check(true, "room strategy default consturction");

    test.summary();
}