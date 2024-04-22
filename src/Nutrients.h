#pragma once
#include "Nutrient.h"
#include <algorithm>

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
    vector<Nutrient> sortedNutrient;

    // Constructor initializing all nutrients
    Nutrients() :
        calories("Calories", "", 0, 0),
        totalFat("Total lipid (fat)", "", 0, 0),
        saturatedFat("Fatty acids, total saturated", "", 0, 0),
        transFat("Fatty acids, total trans", "", 0, 0),
        cholesterol("Cholesterol", "", 0, 0),
        sodium("Sodium, Na", "", 0, 0),
        totalCarbohydrates("Carbohydrate, by difference", "", 0, 0),
        fiber("Fiber, total dietary", "", 0, 0),
        sugar("Sugars, Total", "", 0, 0),
        addedSugar("Sugars, added", "", 0, 0),
        protein("Protein", "", 0, 0),
        vitaminC("Vitamin C", "", 0, 0),
        vitaminD("Vitamin D (D2 + D3)", "", 0, 0),
        iron("Iron, Fe", "", 0, 0),
        calcium("Calcium, Ca", "", 0, 0),
        potassium("Potassium, K", "", 0, 0),
        phosphorus("Phosphorus, P", "", 0, 0) {}


    std::vector<Nutrient> sortNutrientVec() {
        if (calories.amount != 0) {
            sortedNutrient.push_back(calories);
        }
        if (totalFat.amount != 0) {
            sortedNutrient.push_back(totalFat);
        }
        if (saturatedFat.amount != 0) {
            sortedNutrient.push_back(saturatedFat);
        }
        if (transFat.amount != 0) {
            sortedNutrient.push_back(transFat);
        }
        if (cholesterol.amount != 0) {
            sortedNutrient.push_back(cholesterol);
        }
        if (sodium.amount != 0) {
            sortedNutrient.push_back(sodium);
        }
        if (totalCarbohydrates.amount != 0) {
            sortedNutrient.push_back(totalCarbohydrates);
        }
        if (fiber.amount != 0) {
            sortedNutrient.push_back(fiber);
        }
        if (sugar.amount != 0) {
            sortedNutrient.push_back(sugar);
        }
        if (addedSugar.amount != 0) {
            sortedNutrient.push_back(addedSugar);
        }
        if (protein.amount != 0) {
            sortedNutrient.push_back(protein);
        }
        if (vitaminC.amount != 0) {
            sortedNutrient.push_back(vitaminC);
        }
        if (vitaminD.amount != 0) {
            sortedNutrient.push_back(vitaminD);
        }
        if (iron.amount != 0) {
            sortedNutrient.push_back(iron);
        }
        if (calcium.amount != 0) {
            sortedNutrient.push_back(calcium);
        }
        if (potassium.amount != 0) {
            sortedNutrient.push_back(potassium);
        }
        if (phosphorus.amount != 0) {
            sortedNutrient.push_back(phosphorus);
        }

        sort(sortedNutrient.begin(), sortedNutrient.end(), [](const Nutrient& a, const Nutrient& b) {
            return a.amount > b.amount; // Assuming Nutrient class has an amount member variable
            });

        // Returning the sorted vector
        return sortedNutrient;

    }

};