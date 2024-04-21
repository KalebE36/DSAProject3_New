#pragma once
#include <list>
#include <vector>
#include <utility> // For std::pair
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
        //  Constructor initializes key and value using move semantics for efficiency
    };

private:
    std::vector<std::list<Node>> table;         //     Hash table implemented as a vector of linked lists (for chaining)
    size_t bucketCount;                         //     Number of buckets in the hash table
    size_t elemCount;                           //     Number of Elements 
    double maxLoadFactor;                       //     Default Maximum load factor before triggering a rehash
    std::hash<Key> hasher;                      //     Hash function object to compute hashes of keys, Default hasher for type key


public:
    // Constructor
    HashTable(size_t initBucketCount = 10000, double loadFactor = 0.75) {
        bucketCount = initBucketCount;  // Setting the number of buckets
        maxLoadFactor = loadFactor;     // Setting the maximum load factor
        table.resize(bucketCount);      // Resizing the table to the number of buckets
        elemCount = 0;                  // Initializing element count to zero
    }


    // Copy constructor
    HashTable(const HashTable& other):
        bucketCount(other.bucketCount),
        elemCount(other.elemCount),
        maxLoadFactor(other.maxLoadFactor),
        table(other.bucketCount) {
            for (size_t i = 0; i < other.bucketCount; ++i) {
                for (const Node& node : other.table[i]) {
                    table[i].emplace_back(node.key, node.value);
                }
        }
    }


    // Copy assignment operator
    HashTable& operator=(const HashTable& other) {
        if (this != &other) {
            HashTable temp(other);  // Create a temporary copy using the copy constructor
            swap(temp);  // Swap the current object's members with the temporary copy's members
        }
        return *this;
    }


    // Swap member function
    void swap(HashTable& other) noexcept {
        using std::swap;
        swap(bucketCount, other.bucketCount);
        swap(elemCount, other.elemCount);
        swap(maxLoadFactor, other.maxLoadFactor);
        swap(table, other.table);  // Efficiently swaps the contents of the table
    }


    // Move constructor
    HashTable(HashTable&& other) noexcept
        : bucketCount(std::exchange(other.bucketCount, 0)), elemCount(std::exchange(other.elemCount, 0)),
        maxLoadFactor(std::exchange(other.maxLoadFactor, 0.75)), table(std::move(other.table)) {}

    
    // Explicit constructor using specific settings (if needed)
    explicit HashTable(bool specializedConfiguration)
        : bucketCount(specializedConfiguration ? 5000 : 1000),
        maxLoadFactor(specializedConfiguration ? 0.9 : 0.75),
        table(bucketCount), elemCount(0) {}

    // Explicit constructor use example while efficiency demonstration: 
    //  HashTable<int, FoodItem> myHashTable;  // Uses default settings
    //  HashTable<int, FoodItem> customHashTable(500, 0.8);  // Custom settings
    //  HashTable<int, FoodItem> largeHashTable(true);  // Uses the explicit constructor for specialized settings


    // Default destructor is sufficient
    ~HashTable() = default;  // Utilize the default destructor


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
        size_t index = hashKey(key);  // Compute the hash index for the key
        auto& bucket = table[index];  // Reference to the bucket

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->key == key) {  // If the key is found
                bucket.erase(it);  // Erase the node
                --elemCount;       // Decrement the count of elements
                return true;       // Return true indicating successful removal
            }
        }
        return false;  // Return false if the key was not found
    }


    // Existing automatic rehash triggered by load factor
    void rehash() {
        bucketCount *= 2;                           //     Double the number of buckets
        std::vector<std::list<Node>> newTable(bucketCount);  // Create a new table with the increased number of buckets
        for (auto& bucket : table) {                //     Iterate over all buckets
            for (auto& node : bucket) {             //     Iterate over all nodes in each bucket
                newTable[hashKey(node.key)].emplace_back(std::move(node.key), std::move(node.value));
                //     Move each node to the new table at the new index
            }
        }
        table = std::move(newTable);                //     Replace the old table with the new table
    }


    Value* find(const Key& key) {
        size_t index = hashKey(key);
        for (auto& node : table[index]) {
            if (node.key == key) {
                return &node.value;
            }
        }
        return nullptr;
    }


    double loadFactor() const {
        return static_cast<double>(elemCount) / static_cast<double>(bucketCount);
    }


    size_t BucketSize(size_t index) const {
        return table[index].size();
    }


    size_t BucketCount() const {
        return bucketCount;
    }


    size_t Count(const Key& key) {
        return find(key) ? 1 : 0;
    }


    // Clear all elements from the hash table
    void clear() {
        for (auto& bucket : table) {
            bucket.clear();
        }
        elemCount = 0;
    }


    // Check if the hash table is empty
    bool empty() const {
        return size() == 0;
    }


    // Return the current number of elements in the hash table
    size_t size() const {
        size_t size = 0;
        for (const auto& bucket : table) {
            size += bucket.size();
        }
        return size;
    }
};
