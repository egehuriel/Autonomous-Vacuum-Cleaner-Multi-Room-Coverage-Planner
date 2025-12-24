#include <cassert>
#include <iostream>
#include "data_structures/Stack.h"

using ds::Stack;
void test_stack(){
    std::cout << "[UNIT] Stack\n";
    Stack<int> s;
    assert(s.isEmpty());
    s.push(1);
    s.push(2);
    s.push(3);
    assert(s.size() == 3);
    assert(s.top() == 3);
    assert(s.pop() == 3);
    assert(s.pop() == 2);
    assert(s.pop() == 1);
    assert(s.isEmpty());

    std::cout << "PASSED" << std::endl;
}


