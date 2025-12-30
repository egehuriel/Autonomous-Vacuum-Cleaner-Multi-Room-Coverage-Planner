#include <iostream>

void test_linkedlist();
void test_queues();
void test_stack();
void test_hashset();
void test_parser();

int main(){
    try{
        test_linkedlist();
        test_queues();
        test_stack();
        test_hashset();
        test_parser();
    }
    catch(const std::exception& e){
        std::cerr << "TEST FAIL: " << e.what() << std::endl;
        return 1;
    }
}