#include <cassert>
#include <iostream>
#include "data_structures/LinkedList.h"
#include "../tests/unit/TestUtil.hpp"

using ds::LinkedList;

void test_linkedlist(){
    std::cout << "test/unit/ [LINKEDLIST]\n";
    Test test;
    // 1) empty state
    {
        LinkedList<int> list1;
        test.check(list1.getSize() == 0, "new list size == 0");
        test.check(list1.isEmpty() == true, "new list isEmpty == true");
    }
    // 2) pushBack order + front
    {
        LinkedList<int> list2;
        list2.pushBack(1);
        list2.pushBack(2);
        list2.pushBack(3);
        test.check(list2.getSize() == 3, "pushBack x3 increases size");
        test.check(list2.front() == 1, "front after pushBack is first element");
        test.check(list2.get(0) == 1 && list2.get(1) == 2 && list2.get(2) == 3, "get(i) returns correct order");
    }
    // 3) pushFront order
    {
        LinkedList<int> list3;
        list3.pushFront(1);
        list3.pushFront(2);
        list3.pushFront(3);
        test.check(list3.front() == 3, "front after pushFront is last pushed");
        test.check(list3.getSize() == 3, "pushFront x3 increases size");
        test.check(list3.get(0) == 3 && list3.get(1) == 2 && list3.get(2) == 1, "pushFront order correct");
    }
    // 4) popFront updates size and head
    {
        LinkedList<int> list4;
        list4.pushBack(10);
        list4.pushBack(20);
        int x = list4.popFront();
        test.check(x == 10, "popFront returns first element");
        test.check(list4.getSize() == 1, "popFront decrements size");
        test.check(list4.front() == 20, "front updates after popFront");
    }
    // 5) removeFirst: head/middle/tail + not found
    {
        LinkedList<int> list5;
        list5.pushBack(1);
        list5.pushBack(2);
        list5.pushBack(3);
        list5.pushBack(4);
        int v1 = 1;
        int v3 = 3;
        int v4 = 4;
        int v9 = 9;
        test.check(list5.removeFirst(&v1) == true, "removeFirst removes head");
        test.check(list5.getSize() == 3, "size after removing head");
        test.check(list5.removeFirst(&v3) == true, "removeFirst removes middle");
        test.check(list5.getSize() == 2, "size after removing middle");
        test.check(list5.removeFirst(&v4) == true, "removeFirst removes tail");
        test.check(list5.getSize() == 1, "size after removing tail");
        test.check(list5.removeFirst(&v9) == false, "removeFirst returns false if not found");
    }
    // 6) copy constructor deep copy
    {
        LinkedList<int> list6;
        list6.pushBack(7);
        list6.pushBack(8);
        LinkedList<int> list6_2(list6);
        test.check(list6_2.getSize() == 2, "copy ctor copies size");
        test.check(list6_2.get(0) == 7 && list6_2   .get(1) == 8, "copy ctor copies values");
    }
    test.summary();
}