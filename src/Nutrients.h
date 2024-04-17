#pragma once
#include "Nutrient.h"

class Nutrients {
public:
    Nutrient calories;
    Nutrient totalFat;
    Nutrient saturatedFat;
    Nutrient transFat;
    Nutrient cholesterol;
    Nutrient sodium;
    Nutrient totalCarbohydrates;
    Nutrient fiber;
    Nutrient sugar;
    Nutrient addedSugar;
    Nutrient protein;
    Nutrient vitaminC;
    Nutrient vitaminD;
    Nutrient iron;
    Nutrient calcium;
    Nutrient potassium;
    Nutrient phosphorus;

    // Constructor initializing all nutrients
    Nutrients() :
        calories("Calories", 0, 0),
        totalFat("Total Fat", 0, 0),
        saturatedFat("Saturated Fat", 0, 0),
        transFat("Trans Fat", 0, 0),
        cholesterol("Cholesterol", 0, 0),
        sodium("Sodium", 0, 0),
        totalCarbohydrates("Total Carbohydrates", 0, 0),
        fiber("Fiber", 0, 0),
        sugar("Sugar", 0, 0),
        addedSugar("Added Sugar", 0, 0),
        protein("Protein", 0, 0),
        vitaminC("Vitamin C", 0, 0),
        vitaminD("Vitamin D", 0, 0),
        iron("Iron", 0, 0),
        calcium("Calcium", 0, 0),
        potassium("Potassium", 0, 0),
        phosphorus("Phosphorus", 0, 0) {}
};
