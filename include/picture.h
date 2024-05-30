#pragma once
#include <iostream>
#include <vector>
#include <random>
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
            size_t temp = 0;
            if constexpr (is_same_v<K, string>) {
                for (auto c : key) {
                    temp += static_cast<size_t>(c);
                }
            }
            else {
                temp = static_cast<size_t>(key);
            }
            float i = 0.59384;
            return (temp + static_cast<size_t>(i)) % table.size();
        }
    public:
        HashTable(int size) : capacity(size) {
            table.resize(capacity);
        }
        HashTable(int size, int a, int b) : capacity(size) {
            table.resize(capacity);
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<int> distribution(a, b);
            for (int i = 0; i < size; i++) {
                insert(i, distribution(gen));
            }
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
                    table[index] = HashElement<K, T>();
                    return;
                }
                index = (index + 1) % capacity;
            }
            throw out_of_range("Key not found in the hash table.");
        }
        int count(K key) {
            int res = 0;
            for (auto c : table) {
                if (c.key == key) {
                    res++;
                }
            }
            return res;
        }
        int duplicates_count() {
            int duplicate_count = 0;

            for (size_t i = 0; i < table.size(); ++i) {
                if (table[i].filled) {
                    int count = 0;
                    for (size_t j = i; j < table.size(); ++j) {
                        if (table[j].filled && table[j].value == table[i].value) {
                            count++;
                        }
                    }
                    if (count > 1) {
                        duplicate_count += count - 1;
                        for (size_t j = 0; j < table.size(); ++j) {
                            if (table[j].filled && table[j].value == table[i].value) {
                                table[j].filled = false;
                            }
                        }
                    }
                }
            }
            for (size_t i = 0; i < table.size(); ++i) {
                if (!table[i].filled && table[i].value != T()) {
                    table[i].filled = true;
                }
            }

            return duplicate_count;
        }
    };

}