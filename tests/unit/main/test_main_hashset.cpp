#include <iostream>
#include <exception>

void test_hashset();

int main() {
    try{
        test_hashset();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "TEST FAIL : " << e.what() << std::endl;
        return 1;
    }
}