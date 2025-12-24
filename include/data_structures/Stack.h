#pragma once
#include "LinkedList.h"
#include <stdexcept>

namespace ds{
    template <typename T>
    class Stack{
private:
        LinkedList<T> list;
public:
        Stack() = default;

        bool isEmpty(){
            return list.isEmpty();
        }
        size_t size(){
            return list.getSize();
        }
        void push(T&& value){
            list.pushFront(value);
        }
        T pop(){
            if(list.isEmpty()){
                std::cerr <<"empty "<< std::endl;
            }
            return list.popFront();
        }

        T top(){
            if(list.isEmpty()){
                std::cerr << "empty" << std::endl;
            }
            return list.front();
        }
    };
}