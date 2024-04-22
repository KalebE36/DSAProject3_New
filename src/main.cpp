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
    cout << "2. Compare Nutrition Facts\n";
    cout << "3. Exit\n";
}




void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}




int main() {
    auto startTimer = chrono::high_resolution_clock::now();
    FoodDatabase<FoodItem> db;
    DataParser parser;
    cout << "Loading..." << endl;
    parser.loadFiles(db);
    // Populate FoodItems from food.csv
    clearScreen();
    auto endTimer = chrono::high_resolution_clock::now();
    auto durationMTIMER = chrono::duration_cast<chrono::minutes>(endTimer - startTimer);
    auto durationSTIMER = chrono::duration_cast<chrono::seconds >(endTimer - startTimer);



    cout << "Loading time: " << durationMTIMER.count() << "." << durationSTIMER.count() <<  " Minutes" << endl;
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
            db.NutritionFactsComparisonID(db);
            break;
        default:
            cout << "Thank you for using NutritiousDB. Goodbye!\n";
        }
    } while (selection > 2);


    return 0;
}
