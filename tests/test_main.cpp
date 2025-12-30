#include <iostream>

void test_linkedlist();
void test_queues();
void test_stack();
void test_hashset();
void test_parser();
void test_battery();
void test_pathfinder();

int main(){
    try{
        test_linkedlist();
        test_queues();
        test_stack();
        test_hashset();
        test_parser();
        test_battery();
        test_pathfinder();
    }
    catch(const std::exception& e){
        std::cerr << "TEST FAIL: " << e.what() << std::endl;
        return 1;
    }
}