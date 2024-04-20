#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <algorithm> // For std::sort in rankByNutrient()
#include "RedBlackTree.h"

using namespace std;

template<typename T>
class FoodDatabase {
private:
    RedBlackTree<int, T> foodItems; // Assuming our ID is int for now, will need to adjust this If we decide to use string

public:
    // Add a new item

    // Get an item by ID using the RedBlackTree
    T* getItemById(const string& id) {
        return foodItems.search(id);  // make sure search returns a pointer to T
    }

    // Get items by description using the map





    // a more complex function that uses the RedBlackTree's ordered properties
    /* What is even the purpose of this function */
    void displaySortedItems() {
        vector<T> values = foodItems.getAllValues();  // TO DO: RedBlackTree has this method ?? Test it
        for (const T& item : values) {
            cout << item << endl;  // TO DO: operator<< need to be defined for T
        }
    }

    void setRBT(RedBlackTree<int, T>& RBT) {
        foodItems = RBT;
    }

    RedBlackTree<int, T> getRBT() {
        return foodItems;
    }
};
