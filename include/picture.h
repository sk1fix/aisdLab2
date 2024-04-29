#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
using namespace std;
namespace Hash {
    template<typename K, typename T>
    struct HashElement {
        K key;
        T value;
        bool filled;
        HashElement() : filled(false) {}
    };
    template<typename K, typename T>
    class HashTable {
    private:
        vector<HashElement<K, T>> table;
        int capacity;
        unsigned int hashFunction(K key) {
            unsigned int temp = std::hash<K>{}(key);
            return (temp * 2654435761) % capacity;
        }
    public:
        HashTable(int size) : capacity(size) {
            table.resize(capacity);
        }
        void insert(K key, T value) {
            unsigned int index = hashFunction(key);
            while (table[index].filled) {
                index = (index + 1) % capacity;
            }
            table[index].key = key;
            table[index].value = value;
            table[index].filled = true;
        }
        T search(K key) {
            unsigned int index = hashFunction(key);
            while (table[index].filled) {
                if (table[index].key == key) {
                    return table[index].value;
                }
                index = (index + 1) % capacity;
            }
            throw out_of_range("Key not found in the hash table.");
        }
        void remove(K key) {
            unsigned int index = hashFunction(key);
            while (table[index].filled) {
                if (table[index].key == key) {
                    table[index].filled = false;
                    return;
                }
                index = (index + 1) % capacity;
            }
            throw out_of_range("Key not found in the hash table.");
        }
    };
}