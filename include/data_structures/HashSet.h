#pragma once

#include <cstddef>
#include <functional>
#include <stdexcept>
#include <utility>
#include <iostream>

namespace ds {
template <typename Key, typename Hasher = std::hash<Key>, typename KeyEqual = std::equal_to<Key>>
class HashSet{
private:
    struct Entry{
        Key key;
        Entry* next;
        explicit Entry(const Key& k) : key(k), next(nullptr) {}
        explicit Entry(Key&& k) : key(std::move(k)), next(nullptr) {}
    };
    struct Bucket{
        std::size_t index;
        Entry* head;
        Bucket* next;
        explicit Bucket(std::size_t index) : index(index), head(nullptr), next(nullptr) {}
    };
    Bucket* bucketHead;
    std::size_t bucketCount;
    std::size_t size;
    Hasher hasher;
    KeyEqual keyEqual;
    std::size_t bucketIndex(const Key& key) const {
        return hasher(key) % bucketCount;
    }
    Bucket* findBucket(std::size_t index) const{
        Bucket* current = bucketHead;
        while (current != nullptr) {
            if (current->index == index) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    Bucket* get_createBucket(std::size_t index){
        Bucket* bucket = findBucket(index);
        if(bucket != nullptr){
            return bucket;
        }
        Bucket* newBucket = new Bucket(index);
        newBucket -> next = bucketHead;
        bucketHead = newBucket;
        return newBucket;
    }
    void freeBucket(Entry* entry){
        while(entry != nullptr){
            Entry* old = entry -> next;
            delete entry;
            entry = old;
        }
    }
    
public:
    void clear();

    HashSet(std::size_t bucketCount = 1024) : bucketHead(nullptr), bucketCount(bucketCount), size(0), hasher(), keyEqual() {
        if (bucketCount == 0) {
            throw std::invalid_argument("bucket count 0");
        }
    }
    ~HashSet(){
        clear();
    }
    HashSet(HashSet&& other) : bucketHead(nullptr), bucketCount(other.bucketCount), size(0), hasher(other.hasher), keyEqual(other.keyEqual){
        Bucket* current = other.bucketHead;
        while(current != nullptr){
            Entry* entry = current -> head;
            while(entry != nullptr){
                insert(entry -> key);
                entry = entry -> next;
            }
            current = current -> next;
        }
    }


    bool insert(const Key& key){
        std::size_t index = bucketIndex(key);
        Bucket* bucket = get_createBucket(index);

        for (Entry* cur = bucket->head; cur != nullptr; cur = cur->next) {
            if (keyEqual(cur->key, key)) return false;
        }

        Entry* entry = new Entry(key);
        entry->next = bucket->head;
        bucket->head = entry;
        ++size;
        return true;
    }

    bool find(const Key& key) const {
        std::size_t index = bucketIndex(key);
        Bucket* bucket = findBucket(index);
        if(bucket == nullptr){
            return false;
        }
        Entry* entry = bucket -> head;
        while(entry != nullptr){
            if(keyEqual(entry -> key, key)){
                return true;
            }
            entry = entry -> next;
        }
        return false;
    }


    bool insert(Key&& key){
        std::size_t index = bucketIndex(key);
        Bucket* bucket = get_createBucket(index);

        for (Entry* cur = bucket->head; cur != nullptr; cur = cur->next) {
            if (keyEqual(cur->key, key)) return false;
        }
        Entry* entry = new Entry(std::move(key));
        entry->next = bucket->head;
        bucket->head = entry;
        ++size;
        return true;
    }

    bool deleteentry(const Key& key){
        std::size_t index = bucketIndex(key);
        Bucket* bucket = findBucket(index);
        if(bucket == nullptr) {
            return false;
        }
        Entry* current = bucket->head;
        Entry* prev = nullptr;
        while(current != nullptr){
            if(keyEqual(current->key, key)){
                if(prev != nullptr) {
                    prev->next = current->next;
                }
                else{
                    bucket->head = current->next;
                } 
                delete current;
                --size;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }
    
    bool isEmpty() const {
        return size == 0;
    }

    bool contains(const Key& key) const {
        return find(key);
    }

    bool erase(const Key& key){
        return deleteentry(key);
    }






};

template <typename Key, typename Hasher, typename KeyEqual>
void HashSet<Key, Hasher, KeyEqual>::clear(){
    Bucket* current = bucketHead;
    while(current != nullptr){
        Bucket* old = current -> next;
        freeBucket(current -> head);
        delete current;
        current = old;
    }
    bucketHead = nullptr;
    size = 0;
}
}
