/*
#include <iostream>
#include "HashTable.h" 
#include "FoodDatabase.h"

using namespace std; 

int main() {
    // Create an instance of HashTable with FoodItem as the template parameter
    HashTable<int, FoodItem> myTable;

    // Populate the HashTable with mock data
    FoodItem item1(1, "Apple");
    item1.addNutrient("Calories", 52, "kcal");
    item1.addNutrient("Total Fat", 0.2, "g");
    item1.addNutrient("Sodium", 1, "mg");
    myTable.insert(1, item1);

    FoodItem item2(2, "Ayran");
    item2.addNutrient("Calories", 70, "kcal");
    item2.addNutrient("Total Fat", 10.0, "g");
    item2.addNutrient("Sodium", 1, "mg");
    myTable.insert(2, item2);

    FoodItem item3(3, "Armut");
    item3.addNutrient("Calories", 75, "kcal");
    item3.addNutrient("Total Fat", 5.0, "g");
    item3.addNutrient("Sodium", 1, "mg");
    myTable.insert(3, item3);

    FoodItem item4(4, "Banana");
    item4.addNutrient("Calories", 89, "kcal");
    item4.addNutrient("Total Fat", 0.3, "g");
    item4.addNutrient("Sodium", 1, "mg");
    myTable.insert(4, item4);

    // Use the populated HashTable to initialize a FoodDatabase
    FoodDatabase<FoodItem> myDatabase;

    // Add items from the HashTable to the FoodDatabase
    for (int i = 1; i <= 4; ++i) {
        FoodItem* item = myTable.find(i); // Retrieve item from HashTable
        if (item) {
            myDatabase.addOrUpdateItem(item); // Add item to FoodDatabase
        }
    }


    // Test functionality of the FoodDatabase
    // 1. Lookup by ID (Key)
    int targetId = 1; // Example ID to search for
    FoodItem* itemById = myDatabase.getItemById(targetId);
    if (itemById) {
        cout << "Item found by ID: " << itemById->getDescription() << endl;
    }
    else {
        cout << "Item not found by ID" << endl;
    }

    // 2. Lookup by Description
    string targetDescription = "Banana"; // Example description to search for
    vector<FoodItem*> itemsByDescription = myDatabase.getItemsByDescription(targetDescription);
    if (!itemsByDescription.empty()) {
        cout << "Items found by description: ";
        for (const auto& item : itemsByDescription) {
            cout << item->getDescription() << " ";
        }
        cout << endl;
    }
    else {
        cout << "No items found by description" << endl;
    }

    // 3. Remove an item and verify removal
    bool removed = myTable.remove(2); // Attempt to remove item with ID 2
    if (removed) {
        cout << "Item 2 removed successfully." << endl;
    }
    else {
        cout << "Failed to remove Item 2." << endl;
    }

    // Verify removal by trying to find the removed item
    FoodItem* removedItem = myTable.find(2);
    if (!removedItem) {
        cout << "Item 2 no longer exists in the HashTable." << endl;
    }
    else {
        cout << "Item 2 is still present: " << removedItem->getDescription() << endl;
    }

    return 0;

};

*/
