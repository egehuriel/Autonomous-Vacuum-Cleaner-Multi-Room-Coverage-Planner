#include <cassert>
#include <iostream>
#include "data_structures/Queues.h"
#include "../tests/unit/TestUtil.hpp"

using ds::Queue;

void test_queues(){
    std::cout << "test/unit/ [QUEUES]" << std::endl;
    Test test;
    {
        Queue<int> queue;
        test.check(queue.isEmpty() == true, "new queue is empty");
    }
    {
        Queue<int> queue;
        queue.enqueue(1);
        queue.enqueue(2);
        queue.enqueue(3);
        test.check(queue.isEmpty() == false, "queue after enqueue is not empty");
        int v1 = queue.dequeue();
        int v2 = queue.dequeue();
        int v3 = queue.dequeue();
        test.check(v1 == 1 && v2 == 2 && v3 == 3, "dequeue returns values correctly");
        test.check(queue.isEmpty() == true, "queue empty after dequeuing ");
    }
    {
        Queue<int> queue;
        queue.enqueue(42);
        (void)queue.dequeue();
        test.check(queue.isEmpty() == true, "queue end empty");
    }
    test.summary();
}