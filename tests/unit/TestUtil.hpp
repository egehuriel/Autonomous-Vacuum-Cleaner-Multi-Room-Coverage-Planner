#pragma once
#include <iostream>
#include <stdexcept>
#include <string>

struct Test {
    int pass = 0;
    int fail = 0;

    void check(bool condition, const std::string& testname){
        if(condition == true){
            std::cout << "[PASS] " << testname << std::endl;
            pass++;
        } else {
            std::cout << "[FAIL] " << testname << std::endl;
            fail++;
        }
    }
    void require(bool condition, const std::string& testname){
        check(condition, testname);
    }
    void summary(){
        std::cout << "[RESULT] : " << pass << " passed. " << fail << " failed." << std::endl << std::endl;
    }
};

template<typename FN>
inline bool exceptionthrows(FN&& fn){
    try{
        fn();
    }catch(const std::runtime_error&){
        return true;
    }
    return false;
}
