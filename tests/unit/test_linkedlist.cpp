#include <cassert>
#include <iostream>
#include "data_structures/LinkedList.h"

using ds::LinkedList;

void test_linkedlist(){
    std::cout << "test/unit/ [LINKEDLIST]" << std::endl;
    LinkedList<int> l;

    //check 
    assert(l.isEmpty());
    assert(l.getSize() == 0);
    l.pushBack(1);
    l.pushBack(2);
    l.pushFront(0);
    assert(l.getSize() == 3);
    assert(l.get(0) == 0);
    assert(l.get(1) == 1);
    assert(l.get(2) == 2);
    int one = 1;
    int notFound = 999;
    assert(l.findFirst(one) == 1);
    assert(l.findFirst(notFound) == l.getSize());

    // remove
    assert(l.removeFirst(&one) == true);
    assert(l.getSize() == 2);
    assert(l.get(0) == 0);
    assert(l.get(1) == 2);
    int x = l.popFront();
    assert(x == 0);
    assert(l.getSize() == 1);
    assert(l.front() == 2);
    assert(l.back() == 2);
    l.clear();
    assert(l.isEmpty());
    assert(l.getSize() == 0);

    // kopyalama
    l.pushBack(10);
    l.pushBack(20);
    LinkedList<int> c(l);
    assert(c.getSize() == 2);
    assert(c.get(0) == 10 && c.get(1) == 20);

    // move
    LinkedList<int> m = std::move(l);
    assert(m.getSize() == 2);
    assert(l.getSize() == 0);

    std::cout << "-------PASSED-------" << std::endl;
}