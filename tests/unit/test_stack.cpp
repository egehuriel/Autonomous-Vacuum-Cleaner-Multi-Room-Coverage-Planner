#include <cassert>
#include <iostream>
#include "data_structures/Stack.h"
#include "../tests/unit/TestUtil.hpp"

using ds::Stack;
void test_stack(){
    std::cout << "test/unit/ [STACK]" <<std::endl;
    Test test;
    //empty
    {
        Stack<int> stack;
        test.check(stack.isEmpty() == true, "new stack empty");
    }
    // last in first out
    {
        Stack<int> stack;
        stack.push(1);
        stack.push(2);
        stack.push(3);
        test.check(stack.isEmpty() == false, "stack after push not empty");
        int v1 = stack.pop();
        int v2 = stack.pop();
        int v3 = stack.pop();
        test.check(v1 == 3 && v2 == 2 && v3 == 1, "pop returns in lifo order");
        test.check(stack.isEmpty() == true, "stack empty after dequeue");
    }
    //push after empty
    {
        Stack<int> stack;
        stack.push(42);
        (void)stack.pop();
        stack.push(223);
        test.check(stack.isEmpty() == false, "stack after push not empty");
        test.check(stack.pop() == 223, "push workds after empty");
    }
    test.summary();
}


