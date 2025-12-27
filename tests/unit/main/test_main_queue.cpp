#include <iostream>
#include <exception>

void test_queues();
int main() {
    try {
        test_queues();
        return 0;
    } catch (const std::exception& e){
        std::cerr << "TEST FAIL : " << e.what() << std::endl;
        return 1;
    }
}