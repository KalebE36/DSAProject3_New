/*
#include <iostream>
#include "HashTable.h" 
#include "FoodDatabase.h"

using namespace std; 

int main() {
    // Create an instance of HashTable with FoodItem as the template parameter
    HashTable<int, FoodItem> myTable;

    // Populate the HashTable with mock data
    // Mock data for FoodItem 1
    FoodItem item1(1, "Apple");
    item1.addNutrient("Calories", 52, "kcal");
    item1.addNutrient("Total Fat", 0.2, "g");
    item1.addNutrient("Sodium", 1, "mg");
    myTable.insert(1, item1);

    FoodItem item3(1, "Ayran");
    item3.addNutrient("Calories", 70, "kcal");
    item3.addNutrient("Total Fat", 10.0, "g");
    item3.addNutrient("Sodium", 1, "mg");
    myTable.insert(1, item3);


    FoodItem item4(4, "Armut");
    item3.addNutrient("Calories", 75, "kcal");
    item3.addNutrient("Total Fat", 5.0, "g");
    item3.addNutrient("Sodium", 1, "mg");
    myTable.insert(4, item4);



    // Mock data for FoodItem 2
    FoodItem item2(2, "Banana");
    item2.addNutrient("Calories", 89, "kcal");
    item2.addNutrient("Total Fat", 0.3, "g");
    item2.addNutrient("Sodium", 1, "mg");
    myTable.insert(2, item2);

    // use the populated HashTable to initialize a FoodDatabase
    FoodDatabase<FoodItem> myDatabase;

    // Add items from the HashTable to the FoodDatabase
    for (int i = 1; i <= 2; ++i) {
        FoodItem* item = myTable.find(i); // Retrieve item from HashTable
        if (item) {
            myDatabase.addOrUpdateItem(item); // Add item to FoodDatabase
        }
    }

    // test the functionalities of the FoodDatabase

    // 1. Lookup by ID (Key)
    int targetId = 1; // Example ID to search for
    FoodItem* itemById = myDatabase.getItemById(targetId);
    if (itemById) {
        // Item found, use 'itemById' pointer to access the item
        std::cout << "Item found by ID: \t " << itemById->getDescription() << std::endl;
    }
    else {
        std::cout << "Item not found by ID" << std::endl;
    }

    // 2. Lookup by Description
    std::string targetDescription = "Banana"; // Example description to search for
    std::vector<FoodItem*> itemsByDescription = myDatabase.getItemsByDescription(targetDescription);
    if (!itemsByDescription.empty()) {
        // Items found, iterate over the vector to access each item
        std::cout << "Items found by description: \t";
        for (const auto& item : itemsByDescription) {
            std::cout << item->getDescription() << std::endl;
        }
    }
    else {
        std::cout << "No items found by description" << std::endl;
    }



    return 0;
};
*/