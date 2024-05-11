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
        HashElement() : key(K()), value(T()), filled(false) {}
        HashElement(K _key, T _value) : key(_key), value(_value), filled(false) {}
    };
    template<typename K, typename T>
    class HashTable {
    private:
        vector<HashElement<K, T>> table;
        int capacity;
        size_t hashFunction(const K& key) {
            float i = 0.59384;
            size_t temp = 0;
            if constexpr (is_same_v<K, string>) {
                for (auto c : key) {
                    temp += int(c);
                }
                return static_cast<size_t>((temp % table.size() + static_cast<size_t>(i)) % table.size());
            }
            else {
                return static_cast<size_t>((key % table.size() + static_cast<size_t>(i)) % table.size());
            }
        }
        void copyHash(const HashTable& other) {
            
        }
    public:
        HashTable(int size) : capacity(size) {
            table.resize(capacity);
        }
        HashTable(const HashTable& other) {
            capacity = other.capacity;
            table = other.table;
        }
        ~HashTable() {
            table.clear();
            capacity = 0;
        }
        HashTable& operator=(const HashTable& other) {
            if (this != &other) {
                capacity = other.capacity;
                table = other.table;
            }
            return *this;
        }
        void insert(K key, T value) {
            size_t index = hashFunction(key);
            while (table[index].filled) {
                index = (index + 1) % capacity;
            }
            table[index].key = key;
            table[index].value = value;
            table[index].filled = true;
        }
        bool contains(T value) {
            for (auto c : table) {
                if (c.value == value) {
                    return true;
                }
            }
            return false;
        }
        void print() {
            for (size_t i = 0; i < table.size(); i++) {
                cout << table[i].key << " : " << table[i].value << endl;
            }
        }
        T search(K key) {
            size_t index = hashFunction(key);
            while (table[index].filled) {
                if (table[index].key == key) {
                    return table[index].value;
                }
                index = (index + 1) % capacity;
            }
            throw out_of_range("Key not found in the hash table.");
        }
        void erase(K key) {
            size_t index = hashFunction(key);
            while (table[index].filled) {
                if (table[index].key == key) {
                    table[index].filled = false;
                    return;
                }
                index = (index + 1) % capacity;
            }
            throw out_of_range("Key not found in the hash table.");
        }
        int count(K key) {
            /*size_t index = hashFunction(key);*/
            size_t res = 0;
            for (auto c : table) {
                if (c.key == key) {
                    res++;
                }
            }
            return res;
        }
    };
}