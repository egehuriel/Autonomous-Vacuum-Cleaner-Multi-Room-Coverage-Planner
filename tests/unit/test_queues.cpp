#include <cassert>
#include <iostream>
#include "data_structures/Queues.h"

using ds::Queue;

void test_queues(){
    std::cout << "test/unit/ QUEUES" << std::endl;
    Queue<int> q;
    assert(q.isEmpty());
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    assert(q.size() == 3);
    assert(q.front() == 1);
    assert(q.dequeue() == 1);
    assert(q.dequeue() == 2);
    assert(q.dequeue() == 3);
    assert(q.isEmpty());

    std::cout << "PASSED" << std::endl;
}