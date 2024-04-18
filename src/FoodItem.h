#pragma once
#include "NutritionFacts.h" 
#include "RBT.h"

class FoodItem {
public:
    string id;
    string description;

    int selectedQuantity;
    string selectedWeight;


    NutritionFacts nutrition;


    std::map<std::string, double> nutrients;
    map<string, pair<double, string>> servings;  // Key is serving description, value is weight and description


    FoodItem(string id, string description, const NutritionFacts& nutrition)
        : id(id), description(description), nutrition(nutrition) {}

    void addNutrient(const std::string& nutrientCode, double amount) {
        nutrients[nutrientCode] = amount;
    }
    void setSelectedQuantity(int quantity) {
        selectedQuantity = quantity;
    }

    void setSelectedWeight(const string& weight) {
        selectedWeight = weight;
    }

    void addServing(const string& description, double weight) {
        servings[description] = make_pair(weight, description);
    }
};
