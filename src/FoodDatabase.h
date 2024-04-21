#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <algorithm> // For std::sort in rankByNutrient()
#include "RedBlackTree.h"
#include "HashTable.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

template<typename T>
class FoodDatabase {
private:
    RedBlackTree<int, T> foodItems; // Assuming our ID is int for now, will need to adjust this If we decide to use string
    HashTable<int, T> foodItemsH;

public:
    // Add a new item

    // Get an item by ID using the RedBlackTree
    T* getItemById(const string& id) {
        return foodItems.search(id);  // make sure search returns a pointer to T
    }

    // Get items by description using the map

    void SearchNutritionFactsName(FoodDatabase<FoodItem>& db) {
        string input;
        cout << "Enter Name of Item: ";
        cin >> input;


    }


    void SearchNutritionFactsID(FoodDatabase<FoodItem>& db) {
        int id;
        string input;
        cout << "Enter food item ID: ";
        cin >> input;
        try {
            id = stoi(input);
        }
        catch (...) {
            cout << "Not A Valid Integer" << endl;
            exit(1);
        }

        try {
            auto startHash = chrono::high_resolution_clock::now();
            vector<Nutrient> sortedNutrientsH = db.getHashTable().search(id)->nutrients.sortNutrientVec();
            auto endHash = chrono::high_resolution_clock::now();
            auto durationSHash = chrono::duration_cast<chrono::seconds>(endHash - startHash);
            auto durationMHash = chrono::duration_cast<chrono::milliseconds>(endHash - startHash);

            cout << "Time taken for hashtable: " << durationSHash.count() << "." << durationMHash.count() << " seconds" << endl;
            cout << "Name: " << db.getHashTable().search(id)->name << ", Description: " << db.getHashTable().search(id)->description << endl;
            
            // Printing each element of the sorted nutrients vector
            for (const Nutrient& nutrient : sortedNutrientsH) {
                cout << nutrient.name << ": " << nutrient.amount << " " << nutrient.unit_name << ", " << endl;
            }
        }
        catch (...) {
            // If not found in hashtable, try searching in the Red-Black Tree
            cout << "Item Does Not Exist" << endl;
        }
        try {
            auto startRBT = chrono::high_resolution_clock::now();
            vector<Nutrient> sortedNutrients = db.getRBT().search(id)->nutrients.sortNutrientVec();
            auto endRBT = chrono::high_resolution_clock::now();
            auto durationSRBT = chrono::duration_cast<chrono::seconds>(endRBT - startRBT);
            auto durationMRBT = chrono::duration_cast<chrono::milliseconds>(endRBT - startRBT);

            cout << "Time taken for RBT: " << durationSRBT.count() << "." << durationMRBT.count() << " seconds" << endl;
            cout << "Name: " << db.getRBT().search(id)->name << ", Description: " << db.getRBT().search(id)->description << endl;

            // Printing each element of the sorted nutrients vector
            for (const Nutrient& nutrient : sortedNutrients) {
                cout << nutrient.name << ": " << nutrient.amount << " " << nutrient.unit_name << ", ";
            }
        }
        catch (...) {
            cout << "Item Does Not Exist" << endl;
        }
    }

    void NutritionFactsComparisonID(FoodDatabase<FoodItem>& db) {
        string input1, input2;
        int id1, id2;
        cout << "Enter two food item ID's: " << endl;
        cin >> input1;
        cin >> input2;
        try {
            id1 = stoi(input1);
            id2 = stoi(input2);
        }
        catch (...) {
            cout << "Not Valid Integers" << endl;
            exit(1);
        }

        try {
            vector<Nutrient> sortedNutrients1 = db.getRBT().search(id1)->nutrients.sortNutrientVec();
            vector<Nutrient> sortedNutrients2 = db.getRBT().search(id2)->nutrients.sortNutrientVec();

            cout << "Name: " << db.getRBT().search(id1)->name << ", Description: " << db.getRBT().search(id1)->description << endl;
            // Printing each element of the sorted nutrients vector
            for (const Nutrient& nutrient : sortedNutrients1) {
                cout << nutrient.name << ": " << nutrient.amount << " " << nutrient.unit_name << ", ";
            }
            cout << endl;
            cout << "Name: " << db.getRBT().search(id2)->name << ", Description: " << db.getRBT().search(id2)->description << endl;
            // Printing each element of the sorted nutrients vector
            for (const Nutrient& nutrient : sortedNutrients2) {
                cout << nutrient.name << ": " << nutrient.amount << " " << nutrient.unit_name << ", ";
            }
        }
        catch (...) {
            cout << "Item Does Not Exist" << endl;
        }

    }

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

    void setHashTable(HashTable<int, T>& hashTable) {
        foodItemsH = hashTable;
    }

    RedBlackTree<int, T> getRBT() {
        return foodItems;
    }


    HashTable<int, T> getHashTable() {
        return foodItemsH;
    }
};
