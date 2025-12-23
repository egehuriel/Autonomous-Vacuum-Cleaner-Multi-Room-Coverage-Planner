#pragma once
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <iostream>
#include <string>

namespace ds{
template <typename T>
class LinkedList{
private:
	struct Node{
		T data;
		Node* next;
		explicit Node(const T& value) : data(value), next(nullptr) {}
		explicit Node(T&& value) : data(std::move(value)), next(nullptr) {}
	};
	Node* head;
	Node* tail;
	std::size_t size;
	Node* nodeAt(std::size_t index) {
		if(index >= size){
			std::cerr << "out of range" << std::endl;
		}
		Node* cur = head;
		for(std::size_t i = 0; i < index; ++i){
			cur = cur -> next;
		}
		return cur;
	}
public:
	LinkedList() : head(nullptr), tail(nullptr), size(0) {}
	~LinkedList(){
		clear();
	}
	LinkedList(LinkedList& other) : head(nullptr), tail(nullptr), size(0) {
		Node* cur = other.head;
		while(cur){
			pushBack(cur->data);
			cur = cur->next;
		}
	}
	LinkedList& operator=(LinkedList& other){
		if(this == &other){
			return *this;
		}
		clear();
		Node* cur = other.head;
		while(cur){
			pushBack(cur->data);
			cur = cur -> next;
		}
		return *this;
	}
	LinkedList(LinkedList&& other) : head(other.head), tail(other.tail), size(other.size){
		other.head = nullptr;
		other.tail = nullptr;
		other.size = 0;
	}
	LinkedList& operator=(LinkedList&& other)  {
		if(this == &other){
			return *this;
		}
		clear();
		head = other.head;
		tail = other.tail;
		size = other.size;
		other.head = nullptr;
		other.tail = nullptr;
		other.size = 0;
		return *this;
	}


	// linked list functions
	void clear(){
		Node* cur = head;
		while(cur){
			Node* nextt = cur -> next;
			delete cur;
			cur = nextt;
		}
		head = nullptr;
		tail = nullptr;
		size = 0;
	}

	void pushFront(const T& value){
		Node* newNode = new Node(value);
		newNode -> next = head;
		head = newNode;
		if(tail == nullptr){
			tail = head;
		}
		++size;
	}

	void pushFront(T&& value){
		Node* newNode= new Node(std::move(value));
		newNode -> next = head;
		head = newNode;
		if(tail == nullptr){
			tail = head;
		}
		++size;
	}
	void pushBack(const T& value){
		Node* newNode = new Node(value);
		if(tail == nullptr){
			head = tail;
			tail = newNode;
			head = newNode;
		}
		else {
			tail -> next = newNode;
			tail = newNode;
		}
		++size;
	}
	void pushBack(T&& value){
		Node* newNode = new Node(std::move(value));
		if(tail == nullptr){
			head = tail;
			tail = newNode;
			head = newNode;
		}
		else {
			tail -> next = newNode;
			tail = newNode;
		}
		++size;
	}
	
	T popFront(){
		if(size == 0){
			std::cerr << "empty" << std::endl;
		}
		Node* old = head;
		T out = std::move(old -> data);
		head = head -> next;
		delete old;
		--size;
		if(size ==0){
			tail = nullptr; head = nullptr;
		}
		return out;
	}

	T& get (std::size_t index){
		return nodeAt(index) -> data;
	}

	bool removeFirst(T* value){
		Node* cur = head;
		Node* prev = nullptr;
		while(cur){
			if(cur -> data == *value){
				if(prev != nullptr){
					prev -> next = cur -> next;
				}else{
					head = cur -> next;
				}
				if(cur == tail){
					tail = prev;
				}
				delete cur;
				--size;
				if(size == 0){
					head = nullptr; tail = nullptr;
				}
				return true;
			}
			prev = cur; cur = cur -> next;
		}
		return false;
	}

	std::size_t findFirst(T& value){
		Node* cur = head;
		std::size_t findindex = 0;
		while(cur){
			if(cur -> data == value){
				return findindex;
			}
			cur = cur -> next;
			++findindex;
		}
		return size;
	}

	T& front(){
		if(size == 0){
			std::cerr << "empty" << std::endl;
		}
		return head -> data;
	}
	T& back(){
		if(size == 0){
			std::cerr << "empty" << std::endl;
		}
		return tail -> data;
	}

	size_t getSize() const {
		return size;
	}

	bool isEmpty() const {
		return size == 0;
	}

};
}