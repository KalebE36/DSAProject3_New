#include "DataParser.h"
#include <iostream>
#include "menu.h"
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
    cout << "4. Optional-Potential Feature: Ratio Analysis Tool\n";
    cout << "5. Optional-Potential Feature: Complete X+Y+Z Nutrient Calculator - Recipe \n";
    cout << "6. Exit\n";
}


// This function will fetch nutrition facts for a given food item based on its fdc_id or description.
// We can implement this with a default serving size (100g) , but leave it flexible for future enhancements.
void SearchNutritionFacts(FoodDatabase<FoodItem>& db) {
    // TO DO:
    // Functionality to search nutrition facts
    string identifier;
    cout << "Enter food item ID or description: ";
    cin >> identifier; // Simplified input; consider getline for full strings
    double servingSize = 100.0; // Default value, can also ask user for this
    // Implementation to search and display nutrition facts


    FoodItem* item = db.getItemById(identifier);
    if (item) {
        std::cout << "Nutrition facts for " << identifier << ":\n";
        item->nutrition.display();
    }
    else {
        std::vector<FoodItem> items = db.getItemsByDescription(identifier);
        if (!items.empty()) {
            for (const auto& itm : items) {
                std::cout << "Nutrition facts for " << itm.description << ":\n";
                itm.nutrition.display();
            }
        }
        else {
            std::cout << "Item not found.\n";
        }
    }
}


//  This function ranks food items based on their nutrient content,
//  either from highest to lowest or vice versa, based on user input.
void NutrientRanking(FoodDatabase<FoodItem>& db) {
    // TO DO: 
    // Functionality for nutrient ranking
    cout << "SearchNutritionFacts method has not been implemented yet.\n";
    cout << "Alexis has been slacking ahsgagshags";
}


//  This function allows comparing the nutrition facts of multiple food items side-by-side.
void NutritionFactsComparison(FoodDatabase<FoodItem>& db) {
    // TO DO:
    // Functionality to compare nutrition facts side by side

    cout << "SearchNutritionFacts method has not been implemented yet.\n";
    cout << "Kaleb has been slacking ahsgagshags";
}

void RatioAnalysis() {
    // TO DO: Functionality for ratio analysis
    cout << "SearchNutritionFacts method has not been implemented yet.\n";
    cout << "Ozlem has been slacking ahsgagshags";

}

void RecipeNutritionFacts() {
    // TO DO:
    // Functionality for the Nutrition Facts calculator of a recipe
    //      -User provides ingredients(FoodItems) and UOM (pair<string double> of Nutrient Description and its nutritional value for the given UOM. 
    //      -This is very complex as it requires a fully implemented flexible serving size for FoodItems and their Nutrition Facts.
    //      -We can consider additional helper functions for just calculating (or retrieiving the values for other 
    cout << "SearchNutritionFacts method has not been implemented yet.\n";
    cout << " Who has been slacking ";

}

// each FoodItem contains NutritionFacts which itself includes all necessary nutrient details,
// a straightforward approach would be to sum these details across all ingredients,
// adjusting for the quantity of each ingredient used in the recipe.
int main () {
    DataParser parser;
    parser.read_food_nutrients();
    parser.readFoodItems(); // Populate FoodItems from food.csv

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
            NutrientRanking(db);
            break;
        case 3:
            NutritionFactsComparison(db);
            break;
        case 4:
            RatioAnalysis();
            break;
        case 5:
            RecipeNutritionFacts();
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
