#include <iostream>
#include <exception>

void test_stack();

int main() {
    try {
        test_stack();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "TEST FAIL : " << e.what() << std::endl;
        return 1;
    }
}