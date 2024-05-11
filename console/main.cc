#pragma once
#include<picture.h>
using namespace Hash;
using namespace std;
int main()
{
    HashTable<int, string> ht(10);
    ht.insert(1, "One");
    ht.insert(2, "Two");
    ht.insert(26, "Twgriho");
    ht.insert(26, "vksj");
    ht.insert(3, "dbn");
    ht.insert(84, "Twgriho");
    ht.insert(8, "dbn");
    ht.insert(45, "Twgriho");
    ht.insert(8, "dbn");
    ht.insert(9, "Twgriho");
    ht.print();
    cout << ht.contains("dbn") << endl;
    cout << ht.count(8) << endl;
    cout << ht.search(1) << endl;
    cout << ht.search(2) << endl;
    ht.erase(1);
    try {
        cout << ht.search(1) << endl;
    }
    catch (const out_of_range& e) {
        cerr << e.what() << endl;
    }
    return 0;
}