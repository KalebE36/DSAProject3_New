#pragma once
#include "Nutrient.h"
#include "Nutrients.h"
#include "RedBlackTree.h"

class FoodItem {
public:
    int id;
    string name;
    string description;

    int selectedQuantity;
    string selectedWeight;
    string servingUnit;
    string servingSize;

    Nutrients nutrients;


    map<string, pair<double, string>> servings;  // Key is serving description, value is weight and description

    FoodItem() {id = 0; name = "NULL"; description = "NULL"; selectedQuantity = 0; selectedWeight = "NULL";}

    FoodItem(int id, string description, Nutrients  nutrients)
        : id(id), description(description), nutrients(nutrients) {}

        /** Not sure that we need this function, can possibly scrap this
    void addNutrient(Nutrient& nutrient) {

    }
         **/
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
