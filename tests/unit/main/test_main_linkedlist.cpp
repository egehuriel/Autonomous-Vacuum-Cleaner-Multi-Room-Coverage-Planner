#include <iostream>
#include <exception>

void test_linkedlist();

int main() {
    try {
        test_linkedlist();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "TEST FAIL: " << e.what() << std::endl;
        return 1;
    }
}