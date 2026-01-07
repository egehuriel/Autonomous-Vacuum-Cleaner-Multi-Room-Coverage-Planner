#include <iostream>
#include <exception>

void test_battery();

int main(){
    try{
        test_battery();
        return 0;
    } catch(const std::exception& error){
        std::cerr << "TEST FAIL" << error.what() << std::endl;
        return 1;
    }
}