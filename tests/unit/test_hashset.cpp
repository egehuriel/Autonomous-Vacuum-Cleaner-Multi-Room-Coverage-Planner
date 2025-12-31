#include <cassert>
#include <iostream>
#include "data_structures/HashSet.h"
#include "../tests/unit/TestUtil.hpp"

using ds::HashSet;
void test_hashset(){
    std::cout << "test/unit/ [HASH-SET]" << std::endl;
    Test test;
    {
        HashSet<int> set(4);
        test.check(set.isEmpty() == true, "new set is empty");
        test.check(set.insert(223) == true, "insert new return true");
        test.check(set.insert(223) == false, "insert duplicate return false");
        test.check(set.contains(223) == true, "contains returnes true");
        test.check(set.contains(892) == false, "contains false returnes false");
    }
    {
        HashSet<std::string> set(4);
        test.check(set.insert("a") == true, "insert a");
        test.check(set.insert("b") == true, "insert b");
        test.check(set.contains("a") == true, "contains a");
        test.check(set.contains("b") == true, "contains b");
        test.check(set.contains("c") == false, "contains c false");
    }
    test.summary();

}
