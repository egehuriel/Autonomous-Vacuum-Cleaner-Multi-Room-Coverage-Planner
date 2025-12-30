#include <iostream>
#include <exception>

void test_parser();

int main(){
    try{
        test_parser();
        return 0;
    }catch(const std::exception& error){
        std::cerr << "TEST FAIL " << error.what() << std::endl;
        return 1;
    }
}