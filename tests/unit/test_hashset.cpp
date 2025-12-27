#include <cassert>
#include <iostream>
#include "data_structures/HashSet.h"

using ds::HashSet;
void test_hashset(){
    std::cout << "test/unit/ [HASH-SET]" << std::endl;

    HashSet<int> setint(64);
    assert(setint.isEmpty());
    assert(setint.insert(10) == true);
    assert(setint.insert(10) == false);
    assert(setint.contains(10) == true);
    assert(setint.contains(11) == false);
    assert(setint.erase(10) == true);
    assert(setint.erase(10) == false);
    assert(setint.contains(10) == false);
    
    HashSet<std::string> stringset(64);
    stringset.insert("a");
    stringset.insert("b");
    assert(stringset.contains("a"));
    assert(stringset.contains("b"));

    std::cout << "-------PASSED-------" << std::endl; 
}
