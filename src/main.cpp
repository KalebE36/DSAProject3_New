#include "DataParser.h"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "FoodDatabase.h"


using namespace std;
void DisplayMainMenu() {
    cout << endl;
    cout << "Welcome to NutritiousDB - Your Personal Nutrition Guide\n";
    cout << "Please select an option:\n";
    cout << "1. Search Nutrition Facts\n";
    cout << "2. Search NF Name\n";
    cout << "3. Nutrient Ranking Tool\n";
    //cout << "4. Optional-Potential Feature: Ratio Analysis Tool\n";
    //cout << "5. Optional-Potential Feature: Complete X+Y+Z Nutrient Calculator - Recipe \n";
    cout << "4. Exit\n";
}




void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}




int main() {
    FoodDatabase<FoodItem> db;
    DataParser parser;
    cout << "Loading..." << endl;
    parser.loadFiles(db);
    // Populate FoodItems from food.csv
    clearScreen();
    int selection = 0;

    do {
        DisplayMainMenu();
        cout << "Enter your choice: ";
        cin >> selection;
        switch (selection) {
        case 1:
            db.SearchNutritionFactsID(db);
            break;
        case 2:
            db.SearchNutritionFactsName(db);
            break;
        case 3:
            db.NutritionFactsComparisonID(db);
            break;
        case 4:
            //RecipeNutritionFacts();
            break;
        case 5:
            cout << "Thank you for using NutritiousDB. Goodbye!\n";
            break;
        default:
            cout << "Invalid option. Please try again.\n";
        }
    } while (selection != 6);


    return 0;
}
