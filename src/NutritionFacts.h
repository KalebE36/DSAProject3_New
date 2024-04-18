
#pragma once
#include "Nutrients.h"

class NutritionFacts {
public:

    Nutrients nutrients;
    std::string servingDescription;

    NutritionFacts() {servingDescription = "";}
    //explicit NutritionFacts(std::string servingDescription = "") : servingDescription(std::move(servingDescription)) {}

    // Add or update nutrients by specifying the nutrient name and adjustments
    void addOrUpdateNutrient(const std::string& nutrientName, double amount, double dailyValue) {
        Nutrient* nutrient = nullptr; // Pointer to the nutrient to be updated

        // Match the nutrient name to the correct nutrient
        if (nutrientName == "calories") nutrient = &nutrients.calories;
        else if (nutrientName == "totalFat") nutrient = &nutrients.totalFat;
        else if (nutrientName == "saturatedFat") nutrient = &nutrients.saturatedFat;
        else if (nutrientName == "transFat") nutrient = &nutrients.transFat;
        else if (nutrientName == "cholesterol") nutrient = &nutrients.cholesterol;
        else if (nutrientName == "sodium") nutrient = &nutrients.sodium;
        else if (nutrientName == "totalCarbohydrates") nutrient = &nutrients.totalCarbohydrates;
        else if (nutrientName == "fiber") nutrient = &nutrients.fiber;
        else if (nutrientName == "sugar") nutrient = &nutrients.sugar;
        else if (nutrientName == "addedSugar") nutrient = &nutrients.addedSugar;
        else if (nutrientName == "protein") nutrient = &nutrients.protein;
        else if (nutrientName == "vitaminC") nutrient = &nutrients.vitaminC;
        else if (nutrientName == "vitaminD") nutrient = &nutrients.vitaminD;
        else if (nutrientName == "iron") nutrient = &nutrients.iron;
        else if (nutrientName == "calcium") nutrient = &nutrients.calcium;
        else if (nutrientName == "potassium") nutrient = &nutrients.potassium;
        else if (nutrientName == "phosphorus") nutrient = &nutrients.phosphorus;

        // If a valid nutrient was found, update its amount and daily value
        if (nutrient) {
            nutrient->amount += amount;  // Update existing nutrient amount
            nutrient->dailyValue = dailyValue;  // Optionally update the daily value 
        }
    }




    //  Scale Function
    // Multiplication Factor : Each nutrient's amount is multiplied by the given factor.
    //  This is useful for adjusting nutrient values based on quantity differences,
    // (not sure how the final DataSet will have this, might need to update)
    //  such as when calculating nutritional values for different serving sizes or for combining ingredients in a recipe.
    //  Method Returns a New NutritionFacts Object: The method constructs a new NutritionFacts instance with scaled nutrient amounts.
    //  This allows the original NutritionFacts object to remain unchanged, adhering to the principle of immutability for operations
    //  that do not inherently modify the object itself.
    //  This implementation ensures that the scaling applies uniformly across all defined nutrients,
    //  allowing detailed control and manipulation based on specific dietary calculations or recipe requirements.
    
    // Scale all nutrients by a factor for recipe calculations
    NutritionFacts scale(double factor) const {
        NutritionFacts scaled;
        // Scaling each nutrient
        scaled.nutrients.calories.amount = this->nutrients.calories.amount * factor;
        scaled.nutrients.totalFat.amount = this->nutrients.totalFat.amount * factor;
        scaled.nutrients.saturatedFat.amount = this->nutrients.saturatedFat.amount * factor;
        scaled.nutrients.transFat.amount = this->nutrients.transFat.amount * factor;
        scaled.nutrients.cholesterol.amount = this->nutrients.cholesterol.amount * factor;
        scaled.nutrients.sodium.amount = this->nutrients.sodium.amount * factor;
        scaled.nutrients.totalCarbohydrates.amount = this->nutrients.totalCarbohydrates.amount * factor;
        scaled.nutrients.fiber.amount = this->nutrients.fiber.amount * factor;
        scaled.nutrients.sugar.amount = this->nutrients.sugar.amount * factor;
        scaled.nutrients.addedSugar.amount = this->nutrients.addedSugar.amount * factor;
        scaled.nutrients.protein.amount = this->nutrients.protein.amount * factor;
        scaled.nutrients.vitaminC.amount = this->nutrients.vitaminC.amount * factor;
        scaled.nutrients.vitaminD.amount = this->nutrients.vitaminD.amount * factor;
        scaled.nutrients.iron.amount = this->nutrients.iron.amount * factor;
        scaled.nutrients.calcium.amount = this->nutrients.calcium.amount * factor;
        scaled.nutrients.potassium.amount = this->nutrients.potassium.amount * factor;
        scaled.nutrients.phosphorus.amount = this->nutrients.phosphorus.amount * factor;

        return scaled;
    }

    double getNutrientValue(const std::string& nutrientName) const {
        if (nutrientName == "calories") return nutrients.calories.amount;
        else if (nutrientName == "totalFat") return nutrients.totalFat.amount;
        // TO DO :
        // Add other nutrients...


        else return 0; // Return 0 if the nutrient is not found
    }

    //  Operator Overload: The operator+= is being overloaded to add the nutrients from one NutritionFacts instance (other) to another (this).
    //  Nutrient Updates : For each nutrient in the Nutrients class, we access the amount property
    //  and increment it by the amount from the corresponding nutrient in the other NutritionFacts object.
    //  Return Value : This method returns a reference to the current instance(*this), allowing chaining of operations if needed.
    
    // Operator to add another NutritionFacts object's nutrients
    NutritionFacts& operator+=(const NutritionFacts& other) {

        this->nutrients.calories.amount += other.nutrients.calories.amount;
        this->nutrients.totalFat.amount += other.nutrients.totalFat.amount;
        this->nutrients.saturatedFat.amount += other.nutrients.saturatedFat.amount;
        this->nutrients.transFat.amount += other.nutrients.transFat.amount;
        this->nutrients.cholesterol.amount += other.nutrients.cholesterol.amount;
        this->nutrients.sodium.amount += other.nutrients.sodium.amount;
        this->nutrients.totalCarbohydrates.amount += other.nutrients.totalCarbohydrates.amount;
        this->nutrients.fiber.amount += other.nutrients.fiber.amount;
        this->nutrients.sugar.amount += other.nutrients.sugar.amount;
        this->nutrients.addedSugar.amount += other.nutrients.addedSugar.amount;
        this->nutrients.protein.amount += other.nutrients.protein.amount;
        this->nutrients.vitaminC.amount += other.nutrients.vitaminC.amount;
        this->nutrients.vitaminD.amount += other.nutrients.vitaminD.amount;
        this->nutrients.iron.amount += other.nutrients.iron.amount;
        this->nutrients.calcium.amount += other.nutrients.calcium.amount;
        this->nutrients.potassium.amount += other.nutrients.potassium.amount;
        this->nutrients.phosphorus.amount += other.nutrients.phosphorus.amount;

        return *this;
    }

    // Calculate total nutrition from multiple ingredients (for Recipe Function mainly)
    static NutritionFacts calculateTotalNutrition(const std::vector<std::pair<NutritionFacts, double>>& ingredients) {
        NutritionFacts total;
        for (const auto& ingredient : ingredients) {
            const NutritionFacts& nutrition = ingredient.first;
            double quantity = ingredient.second;
            total += nutrition.scale(quantity);
        }
        return total;
    }



    void SearchNutritionFacts(FoodDatabase<FoodItem>& container, const string& identifier, double servingSize = 100.0) {
        FoodItem* item = container.getItemById(identifier);
        if (item) {

            cout << "Nutrition facts for " << item->description << ":\n";
            item->nutrition.display(); // TO DO: We need to implement - down below, fill in the rest for other elements
        }
        else {
            cout << "Item not found.\n";
        }
    }


    // This method is Assuming container can sort and rank items based on nutrient content
    // We may need to add a sorting function to Hashtable, The RBT should be able to handle it as is. 
    void NutrientRanking(FoodDatabase<FoodItem>& container, const string& nutrient, bool highest = true, size_t limit = 100) {
        auto rankedItems = container.rankByNutrient(nutrient, highest, limit); // We need to implement this
        for (const auto& item : rankedItems) {
            cout << item.description << ": " << item.nutrition.getNutrientValue(nutrient) << '\n'; // TO DO: Implement getNutrientValue - not completed
        }
    }


    void NutritionFactsComparison(FoodDatabase<FoodItem>& container, const vector<string>& identifiers) {
        for (const auto& id : identifiers) {
            FoodItem* item = container.getItemById(id);
            if (item) {
                cout << "Nutrition for " << item->description << ":\n";
                item->nutrition.display(); // Display method for nutrition
            }
            else {
                cout << "Item with ID " << id << " not found.\n";
            }
        }
    }

    // Example method to display nutrition facts
    void display() const {
        // TO DO:  Output each nutrient and its value
        cout << "Calories: " << nutrients.calories.amount << " kcal\n";
        // TO DO: Repeat for other nutrients
    }

};
