#include <iostream>

void test_linkedlist();
void test_queues();
void test_stack();
void test_hashset();
void test_parser();
void test_battery();
void test_pathfinder();
void test_coverageplanner();
void test_roomdecomposer();
void test_roomstrategy();

int main(){
    try{
        test_linkedlist();
        test_queues();
        test_stack();
        test_hashset();
        test_parser();
        test_battery();
        test_pathfinder();
        test_coverageplanner();
        test_roomdecomposer();
        test_roomstrategy();
    }
    catch(const std::exception& e){
        std::cerr << "TEST FAIL: " << e.what() << std::endl;
        return 1;
    }
}