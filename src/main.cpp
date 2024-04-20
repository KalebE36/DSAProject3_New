#include "DataParser.h"
#include <iostream>
#include <vector>
#include <string>
#include "FoodDatabase.h"


using namespace std;
void DisplayMainMenu() {
    cout << "Welcome to NutritiousDB - Your Personal Nutrition Guide\n";
    cout << "Please select an option:\n";
    cout << "1. Search Nutrition Facts\n";
    cout << "2. Nutrient Ranking Tool\n";
    cout << "3. Nutrition Facts Comparison\n";
    //cout << "4. Optional-Potential Feature: Ratio Analysis Tool\n";
   //cout << "5. Optional-Potential Feature: Complete X+Y+Z Nutrient Calculator - Recipe \n";
    cout << "4. Exit\n";
}





void SearchNutritionFacts(FoodDatabase<FoodItem>& db) {
    int id;
    cout << "Enter food item ID: ";
    cin >> id;

    try {
        vector<Nutrient> sortedNutrients = db.getRBT().search(id)->nutrients.sortNutrientVec();
        cout << "Name: " << db.getRBT().search(id)->name << ", Description: " << db.getRBT().search(id)->description << endl;
        // Printing each element of the sorted nutrients vector
        for (const Nutrient& nutrient : sortedNutrients) {
            cout << nutrient.name << ": " << nutrient.amount << " " << nutrient.unit_name << ", ";
        }
    }
    catch (...) {
        cout << "Item Does Not Exist" << endl;
    }


    //std::cout << "Nutrition facts for " << id << ":\n";
    //item->nutrients.displayNutrients();


}





int main() {
    FoodDatabase<FoodItem> db;
    DataParser parser;
    parser.loadFiles(db);

    // Populate FoodItems from food.csv
    int selection = 0;

    do {
        DisplayMainMenu();
        cout << "Enter your choice: ";
        cin >> selection;
        switch (selection) {
        case 1:
            SearchNutritionFacts(db);
            break;
        case 2:
            //NutritionFactsComparison(db);
            break;
        case 4:
            // RatioAnalysis();
            break;
        case 5:
            //RecipeNutritionFacts();
            break;
        case 6:
            cout << "Thank you for using NutritiousDB. Goodbye!\n";
            break;
        default:
            cout << "Invalid option. Please try again.\n";
        }
    } while (selection != 6);


    return 0;
}
