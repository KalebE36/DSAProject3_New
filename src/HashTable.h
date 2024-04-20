#pragma once
#include <list>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

//HashTable Template Class Sketch
template <typename Key, typename Value>
class HashTable {
public:
    struct Node {
        Key key;                            //     Key value of the node
        Value value;                        //     Value associated with the key
        Node(Key k, Value v) : key(std::move(k)), value(std::move(v)) {}
        //     Constructor initializes key and value using move semantics for efficiency
    };

private:
    std::vector<std::list<Node>> table;     //     Hash table implemented as a vector of linked lists (for chaining)
    size_t bucketCount;                     //     Number of buckets in the hash table
    size_t elemCount = 0;                   //     Number of Elements 
    double maxLoadFactor;                   //     Maximum load factor allowed before triggering a rehash
    std::hash<Key> hasher;                  //     Hash function object to compute hashes of keys

public:
    // Constructor to initialize the hash table with a specific number of buckets and load factor
    HashTable(size_t initBucketCount = 10, double loadFactor = 0.75)
        : bucketCount(initBucketCount), maxLoadFactor(loadFactor), table(initBucketCount) {}


        // Helper function to compute the bucket index for a given key
    size_t hashKey(const Key& key) {
        return hasher(key) % bucketCount;            //     Hash the key and mod by the number of buckets
    }


    // Helper function to check if the current load factor exceeds the maximum allowed load factor
    bool loadFactorExceeded() {
        size_t totalElements = 0;
        for (const auto& b : table) {                //     Count all elements in the table
            totalElements += b.size();
        }
        return static_cast<double>(totalElements) / static_cast<double>(bucketCount) > maxLoadFactor;
    }


    // Function to insert a key-value pair into the hash table
    bool insert(const Key& key, const Value& value) {
        auto& bucket = table[hashKey(key)];          //     Get the bucket by hashing the key
        for (auto& node : bucket) {                  //     Iterate through the nodes in the bucket
            if (node.key == key) {                   //     Check if the key already exists
                node.value = value;                  //     Update the value if key exists
                return false;                        //     Return false indicating an update, not an insertion
            }
        }
        bucket.emplace_back(key, value);             //     Emplace a new node in the bucket if key does not exist
        ++elemCount;
        if (loadFactorExceeded()) {                  //     Check if the load factor is exceeded
            rehash();                                //     Perform rehash if necessary
        }
        return true;                                 //     Return true indicating a new key-value pair was added
    }


    ////  
//    Value* search(const Key& key) {
//        size_t index = hashFunction(key) % table.size();
//        auto& list = table[index];
//        auto itr = find_if(list.begin(), list.end(), [&key](const pair<Key, Value>& element) { return element.first == key; });
//        if (itr != list.end()) {
//            return &(itr->second);
//        }
//        return nullptr; // Not found
//    }

// Function to search for a value by its key in the hash table
    Value* search(const Key& key) {
        auto& bucket = table[hashKey(key)];          //     Get the bucket by hashing the key
        for (auto& node : bucket) {                  //     Iterate through the nodes in the bucket
            if (node.key == key) {                   //     If key is found
                return &node.value;                  //     Return a pointer to the value
            }
        }
        return nullptr;                              //     Return nullptr if key is not found
    }

// Function to remove a key-value pair from the hash table
    bool remove(const Key& key) {
        auto& bucket = table[hashKey(key)];          //     Get the bucket by hashing the key
        auto it = std::find_if(bucket.begin(), bucket.end(), [&key](const Node& node) {
            return node.key == key;                  //     Find the node with the given key
            });
        if (it != bucket.end()) {                    //     If the node is found
            bucket.erase(it);                        //     Erase the node
            return true;                             //     Return true indicating successful removal
        }
        return false;                                //     Return false if the key was not found
    }

private:
    // Helper function to compute the bucket index for a given key
    size_t hashKey(const Key& key) {
        return hasher(key) % bucketCount;            //     Hash the key and mod by the number of buckets
    }

    // Helper function to check if the current load factor exceeds the maximum allowed load factor
    bool loadFactorExceeded() {
        size_t totalElements = 0;
        for (const auto& b : table) {                //     Count all elements in the table
            totalElements += b.size();
        }
        return static_cast<double>(totalElements) / static_cast<double>(bucketCount) > maxLoadFactor;
    }

    // Function to resize and rehash the hash table
    void rehash() {
        bucketCount *= 2;                           //     Double the number of buckets
        std::vector<std::list<Node>> newTable(bucketCount);  // Create a new table with the increased number of buckets
        for (auto& bucket : table) {                //     Iterate over all buckets
            for (auto& node : bucket) {             //     Iterate over all nodes in each bucket
                newTable[hashKey(node.key)].emplace_back(std::move(node.key), std::move(node.value));
                //     Move each node to the new table at the new index
            }
        }
        table = std::move(newTable);                //     Replace the old table with the new table
    }

    // Returns the curr LoadFactor
    double loadFactor() const {
        return static_cast<double>(elemCount) / static_cast<double>(bucketCount);
    }

    size_t BucketSize(size_t index) const {
        return table[index].size();
    }

    size_t BucketCount() const {
        return bucketCount;
    }

    public:
    // if needed we can define a more sophisticated hash function, especially we we include the categories
    /*

    // Manually triggered rehash to a specific number of buckets
    void rehash(size_t new_bucket_count) {
        if (new_bucket_count > bucketCount) {  // Only rehash if the new size is larger
            std::vector<std::list<Node>> newTable(new_bucket_count);  // Create a new table with specified number of buckets
            for (auto& bucket : table) {  // Iterate over all buckets in the current table
                for (auto& node : bucket) {  // Iterate over all nodes within each bucket
                    size_t new_index = hasher(node.key) % new_bucket_count;  // Recompute the hash index based on the new bucket count
                    newTable[new_index].emplace_back(std::move(node.key), std::move(node.value));  // Move each node to the new table at the new index
                }
            }
            table = std::move(newTable);  // Replace the old table with the new table
            bucketCount = new_bucket_count;  // Update the bucket count to the new value
        }
    }

    // ???
    void rehash(size_t new_buckets = 0) {
        if (new_buckets == 0) new_buckets = bucketCount * 2;  // Default rehash: double the bucket count
        vector<list<Node>> newTable(new_buckets);
        for (auto& bucket : table) {
            for (auto& node : bucket) {
                size_t newIndex = hasher(node.key) % new_buckets;
                newTable[newIndex].push_back(move(node));
            }
        }
        table = move(newTable);
        bucketCount = new_buckets;
    }
    */

    Value* find(const Key& key) {
        size_t index = hashKey(key);
        for (auto& node : table[index]) {
            if (node.key == key) {
                return &node.value;
            }
        }
        return nullptr;
    }

    bool erase(const Key& key) {
        size_t index = hashKey(key);
        auto& bucket = table[index];
        auto it = bucket.begin();
        while (it != bucket.end()) {
            if (it->key == key) {
                bucket.erase(it);
                --elemCount;
                return true;
            }
            ++it;
        }
        return false;
    }

    size_t Count(const Key& key) {
        return find(key) ? 1 : 0;
    }

    // Checks if the hash table is empty
    bool empty() const {
        return size() == 0;
    }

    // Clears all elements from the hash table
    void clear() {
        for (auto& bucket : table) {
            bucket.clear();
        }
        elemCount = 0;
    }

    // Returns the current number of elements in the hash table
    size_t size() const {
        size_t size = 0;
        for (const auto& bucket : table) {
            size += bucket.size();
        }
        return size;
    }
};
