#include <iostream>
#include <exception>

void test_pathfinder();

int main(){
    try{
        test_pathfinder();
        return 0;
    } catch(const std::exception& error){
        std::cerr << "TEST FAIL " << error.what() << std::endl;
        return 1;
    }
}