#pragma once
#include <cstddef>
#include "LinkedList.h"
#include <stdexcept>
#include <iostream>
#include <string>
namespace ds{
template <typename T>
class Queue{
private:
    LinkedList<T> list;
public:
    Queue() = default;
    
    // qeueue functions
    void enqueue(const T& value){
        list.pushBack(value);
    }
    void enqueue(T&& value){
        list.pushBack(std::move(value));
    }
    
    T dequeue(){
        if(list.isEmpty()){
            std::cerr << "empty" << std::endl;
        }
        return list.popFront();
    }
    T& front(){
        if(list.isEmpty()){
            std::cerr << "empty" << std::endl;
        }
        return list.front();
    }

    bool isEmpty(){
        return list.isEmpty();
    }

    size_t size(){
        return list.getSize();
    }


};

}
