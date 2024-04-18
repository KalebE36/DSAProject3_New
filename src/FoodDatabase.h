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
    RedBlackTree<int, T> foodItemsById; // Assuming our ID is int for now, will need to adjust this If we decide to use string
    RedBlackTree<string, vector<T>> foodItemsByDescription;
    vector<T> allItems;  // Maintained as a simple list

public:
    // Add a new item
    void addItem(const string& id, const string& description, const T& item) {
        foodItemsById.insert(id, item);
        foodItemsByDescription[description].push_back(item);
        allItems.push_back(item);
    }

    // Get an item by ID using the RedBlackTree
    T* getItemById(const string& id) {
        return foodItemsById.search(id);  // make sure search returns a pointer to T
    }

    // Get items by description using the map
    vector<T> getItemsByDescription(const string& description) {
        return foodItemsByDescription[description];
    }

    vector<T> rankByNutrient(const string& nutrient, bool highest = true, size_t limit = 100) {
        vector<T> items = getAllItems(); // Copy all items to a new vector

        // Sort the vector based on nutrient value
        sort(items.begin(), items.end(), [&nutrient, highest](const T& a, const T& b) {
            double aValue = a.nutrition.getNutrientValue(nutrient);
            double bValue = b.nutrition.getNutrientValue(nutrient);
            return highest ? aValue > bValue : aValue < bValue; // Sort descending if highest is true, otherwise ascending
        });

        // Trim the vector to the specified limit
        if (items.size() > limit) {
            items.resize(limit);
        }

        return items;
    }

    // Get all items
    vector<T> getAllItems() const {
        return allItems;
    }

    // a more complex function that uses the RedBlackTree's ordered properties
    void displaySortedItems() {
        vector<T> values = foodItemsById.getAllValues();  // TO DO: RedBlackTree has this method ?? Test it
        for (const T& item : values) {
            cout << item << endl;  // TO DO: operator<< need to be defined for T
        }
    }
};
