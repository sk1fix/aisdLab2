#pragma once
#include<picture.h>
using namespace Hash;
int main()
{
    HashTable<int, std::string> ht(10);
    ht.insert(1, "One");
    ht.insert(2, "Two");

    std::cout << ht.search(1) << std::endl;
    std::cout << ht.search(2) << std::endl;
    ht.remove(1);
    try {
        std::cout << ht.search(1) << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}