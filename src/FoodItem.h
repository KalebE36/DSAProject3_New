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


};
