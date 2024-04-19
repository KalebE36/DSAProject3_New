#pragma once
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include "FoodItem.h"
#include "Nutrient.h"
#include "NutritionFacts.h"
#include "RedBlackTree.h"

using namespace std;
/* This is a very general idea of a data parser that we could use for csv files */
class DataParser {
private:
    unordered_map<int, FoodItem> RBT;
    unordered_map<int, string> nutrientIDM;
    unordered_map<int, vector<Nutrient>> nutrientPF;
    unordered_map<int, Nutrients>nutrientsPF;
    fstream currFile;


public:

    void parseFoodCSV() {
        currFile.open("../db/food.csv");
        if(!currFile.is_open()) {
            std::cout << "Error opening food.csv" << std::endl;
            std::exit(1);
        }

        std::string line;
        int count = 0;
        while(getline(currFile, line) && (count < 200000)) {
            std::stringstream ss(line);
            std::string id, data_type, name, food_cat_id, publ_date, market, trade, mic_dat;
            getline(ss, id, ','); getline(ss, data_type, ','); getline(ss, name, ','); getline(ss, food_cat_id, ','); getline(ss, publ_date, ',');
            getline(ss, market, ','); getline(ss, trade, ','); getline(ss, mic_dat, ',');

            id.erase(remove(id.begin(), id.end(), '"'), id.end());
            name.erase(remove(name.begin(), name.end(), '"'), name.end());


            if(count > 0) {
                FoodItem item;
                item.id = stoi(id);
                item.name = name;
                RBT[stoi(id)] = item;
            }
            ++count;
        }
        currFile.close();
    }

    /* parseFoodCSV will be the first FUNCTION CALLED FOR PARSING EACH TIME */
    void parseBrandedFoodCSV() {
        currFile.open("../db/branded_food.csv");
        if(!currFile.is_open()) {
            cout << "Error opening food.csv" << endl;
            exit(1);
        }

        string line;
        int count = 0;
        while(getline(currFile, line) && (count < 200000)) {
            stringstream ss(line);
            string id, name, city, foodCat, description, servSize, servSizeUnit, hhServing, bfoodCat, source, packageWeight, mD, aD, market, dD, pSC, tC, sD;
            getline(ss, id, ','); getline(ss, name, ','); getline(ss, city, ','); getline(ss, foodCat, ',');
            getline(ss, description, ',');getline(ss, servSize, ','); getline(ss, servSizeUnit, ',');
            getline(ss, hhServing, ',');getline(ss, bfoodCat, ',');getline(ss, source, ',');
            getline(ss, packageWeight, ',');getline(ss, mD, ',');getline(ss, aD, ',');
            getline(ss, market, ',');getline(ss, dD, ',');getline(ss, pSC, ',');
            getline(ss, tC, ',');getline(ss, sD, ',');


            description.erase(remove(description.begin(), description.end(), '"'), description.end());
            id.erase(remove(id.begin(), id.end(), '"'), id.end());


            try {

                RBT[stoi(id)].description = description;
            } catch (...) {
                cout << "Error converting id to integer: " << id << endl;               
                continue;
            }
            ++count;
        }
        currFile.close();
    }

    void parseNutrientID() {
        currFile.open("../db/nutrient.csv");
        if(!currFile.is_open()) {
            cout << "Error opening file" << endl;
            exit(1);
        }

        string line;
        while(getline(currFile, line)) {
            stringstream ss(line);
            string id, name, unit_name, nutrient_nbr_str, rank_str;
            getline(ss, id, ',');getline(ss, name, ',');getline(ss, unit_name, ',');
            getline(ss, nutrient_nbr_str, ',');getline(ss, rank_str, ',');

            name.erase(remove(name.begin(), name.end(), '"'), name.end());
            id.erase(remove(id.begin(), id.end(), '"'), id.end());

            int id_num;
            try {
                id_num = stoi(id);
                nutrientIDM[id_num] = name;
            } catch (...) {
                cout << "Error converting id to integer: " << id << endl;
                continue; // Skip this row if id cannot be converted to integer
            }

        }
        currFile.close();
    }

    void parseFoodNutrients() {
        currFile.open("../db/food_nutrient.csv");
        if (!currFile.is_open()) {
            cout << "Error opening file" << endl;
            exit(1);
        }

        string line;
        int count = 0;
        while (getline(currFile, line) && (count < 200000)) {
            stringstream ss(line);
            string rID, fdcID, nutrientID, amount, dP, derV, min, max, median, loq, footnote, minYear, percDV;
            getline(ss, rID, ',');getline(ss, fdcID, ',');getline(ss, nutrientID, ',');
            getline(ss, amount, ',');getline(ss, dP, ',');getline(ss, derV, ',');
            getline(ss, min, ',');getline(ss, max, ',');getline(ss, median, ',');
            getline(ss, loq, ',');getline(ss, footnote, ',');getline(ss, minYear, ',');
            getline(ss, percDV, ',');


            // Remove quotes from the parsed strings
            fdcID.erase(remove(fdcID.begin(), fdcID.end(), '"'), fdcID.end());
            nutrientID.erase(remove(nutrientID.begin(), nutrientID.end(), '"'), nutrientID.end());
            amount.erase(remove(amount.begin(), amount.end(), '"'), amount.end());
            percDV.erase(remove(percDV.begin(), percDV.end(), '"'), percDV.end());

            try {
                // Assuming nutrientIDMap is a map
                if (percDV == "") {
                    percDV = "0.0";
                }
                cout << "FDIC: " << RBT[stoi(fdcID)].name << ", NUTRIENT:  " << nutrientIDM[stoi(nutrientID)] << ", Amount: " << amount << endl;
                Nutrient nutrient(nutrientIDM[stoi(nutrientID)], stod(amount), stoi(percDV));
                nutrientPF[stoi(fdcID)].push_back(nutrient);
            } catch (...) {
                cout << "Error converting something to integer" << endl;
                continue; // Skip this row if id cannot be converted to integer
            }

            ++count;
        }
        currFile.close();
    }

    void createNutrients() {
        for(auto& element : nutrientPF) {
            Nutrients newNutrients;
            for(auto& nutrient : element.second) {
                if (nutrient.name == "calories") {
                    newNutrients.calories = nutrient;
                }
                else if (nutrient.name == "totalFat") {
                    newNutrients.totalFat = nutrient;
                }
                else if (nutrient.name == "saturatedFat") {
                    newNutrients.saturatedFat = nutrient;
                }
                else if (nutrient.name == "transFat") {
                    newNutrients.transFat = nutrient;
                }
                else if (nutrient.name == "Cholesterol") {
                    newNutrients.cholesterol = nutrient;
                }
                else if (nutrient.name == "Sodium") {
                    newNutrients.sodium = nutrient;
                }
                else if (nutrient.name == "Carbohydrates") {
                    newNutrients.totalCarbohydrates = nutrient;
                }
                else if (nutrient.name == "Fiber") {
                    newNutrients.fiber = nutrient;
                }
                else if (nutrient.name == "Sugars") {
                    newNutrients.sugar = nutrient;
                }
                else if (nutrient.name == "addedSugar") {
                    newNutrients.addedSugar = nutrient;
                }
                else if (nutrient.name == "Protein") {
                    newNutrients.protein = nutrient;
                }
                else if (nutrient.name == "vitaminC") {
                    newNutrients.vitaminC = nutrient;
                }
                else if (nutrient.name == "Vitamin D") {
                    newNutrients.vitaminD = nutrient;
                }
                else if (nutrient.name == "Iron") {
                    newNutrients.iron = nutrient;
                }
                else if (nutrient.name == "Calcium") {
                    newNutrients.calcium = nutrient;
                }
                else if (nutrient.name == "Potassium") {
                    newNutrients.potassium = nutrient;
                }
                else if (nutrient.name == "phosphorus") {
                    newNutrients.phosphorus = nutrient;
                }
                else {
                    continue;
                }
            }
            NutritionFacts nf;
            nf.nutrients = newNutrients;
            RBT[element.first].nutrition = nf;
        }
    }

    void testFunction() {
        parseFoodCSV();
        parseBrandedFoodCSV();
        parseNutrientID();
        parseFoodNutrients();
        createNutrients();
        for(auto& element : RBT) {
            cout << "Food Name: " << element.second.name << ", Protein: " << element.second.nutrition.nutrients.protein.amount << ", Daily Value: " << element.second.nutrition.nutrients.protein.dailyValue << "%" << endl;
        }
    }


};



