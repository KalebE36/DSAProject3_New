#pragma once
#include <list>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

// A template class for a HashTable structure will allow us to use it interchangeably with the RedBlackTree for comparison purposes.
// Below is a basic sketch of a HashTable template class, designed with simplicity in mind to get us started.

// This sketch includes fundamental operations like insertion, search, and a basic hashing mechanism.
// More advanced features, such as dynamic resizing or collision resolution strategies beyond chaining,
// need to be added based on our project's requirements.



//HashTable Template Class Sketch
template <typename Key, typename Value>
class HashTable {
public:
    HashTable(size_t size = 101) : table(size) {} // Default size to a prime number for better distribution

    void insert(const Key& key, const Value& value) {
        size_t index = hashFunction(key) % table.size();
        table[index].push_back(make_air(key, value)); // Simple chaining for collision resolution
    }

    Value* search(const Key& key) {
        size_t index = hashFunction(key) % table.size();
        auto& list = table[index];
        auto itr = find_if(list.begin(), list.end(), [&key](const pair<Key, Value>& element) { return element.first == key; });
        if (itr != list.end()) {
            return &(itr->second);
        }
        return nullptr; // Not found
    }

    bool remove(const Key& key) {
        size_t index = hashFunction(key) % table.size();
        auto& list = table[index];
        auto itr = find_if(list.begin(), list.end(), [&key](const pair<Key, Value>& element) { return element.first == key; });
        if (itr != list.end()) {
            list.erase(itr);
            return true;
        }
        return false; // Not found
    }

private:
    vector<list<pair<Key, Value>>> table; // The hash table uses chaining for collision resolution
    hash<Key> hashFunction; // The C++ Standard Library hash function (can be replaced with custom hash function if needed)
                            // TO DO: We need to find out if we are allowed to use STL functions or if those also need to be created from scratch. 

    // Additional private member functions (like rehash) can be added here
};
