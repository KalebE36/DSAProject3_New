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
    RedBlackTree<int, FoodItem> RBT;
    unordered_map<int, string> nutrientIDM;
    unordered_map<int, vector<Nutrient>> nutrientPF;
    unordered_map<int, Nutrients>nutrientsPF;
    fstream currFile;


public:

    /* parseFoodCSV will be the first FUNCTION CALLED FOR PARSING EACH TIME */
    void parseFoodCSV() {
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


            id.erase(remove(id.begin(), id.end(), '"'), id.end());
            description.erase(remove(description.begin(), description.end(), '"'), description.end());
            name.erase(remove(name.begin(), name.end(), '"'), name.end());


            try {
                FoodItem item;
                item.id = stoi(id);
                item.name = name;
                item.description = description;
                RBT.insert(stoi(id), item);
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
        currFile.open("../db/food_attribute.csv");
        if(!currFile.is_open()) {
            cout << "Error opening file" << endl;
            exit(1);
        }

        string line;
        int count = 0;
        while(getline(currFile, line) && (count < 200000)) {
            stringstream ss;
            string fdcID, nutrientID, amount, dP, derV, min, max, median, loq, footnote, minYear, percDV;
            getline(ss, fdcID, ',');getline(ss, nutrientID, ',');getline(ss, amount, ',');
            getline(ss, dP, ',');getline(ss, derV, ',');getline(ss, min, ',');
            getline(ss, max, ',');getline(ss, median, ',');getline(ss, loq, ',');
            getline(ss, footnote, ',');getline(ss, minYear, ',');getline(ss, percDV, ',');

            fdcID.erase(remove(fdcID.begin(), fdcID.end(), '"'), fdcID.end());
            nutrientID.erase(remove(nutrientID.begin(), nutrientID.end(), '"'), nutrientID.end());
            amount.erase(remove(amount.begin(), amount.end(), '"'), amount.end());

            try {

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
                else if (nutrient.name == "cholesterol") {
                    newNutrients.cholesterol = nutrient;
                }
                else if (nutrient.name == "sodium") {
                    newNutrients.sodium = nutrient;
                }
                else if (nutrient.name == "totalCarbohydrates") {
                    newNutrients.totalCarbohydrates = nutrient;
                }
                else if (nutrient.name == "fiber") {
                    newNutrients.fiber = nutrient;
                }
                else if (nutrient.name == "sugar") {
                    newNutrients.sugar = nutrient;
                }
                else if (nutrient.name == "addedSugar") {
                    newNutrients.addedSugar = nutrient;
                }
                else if (nutrient.name == "protein") {
                    newNutrients.protein = nutrient;
                }
                else if (nutrient.name == "vitaminC") {
                    newNutrients.vitaminC = nutrient;
                }
                else if (nutrient.name == "vitaminD") {
                    newNutrients.vitaminD = nutrient;
                }
                else if (nutrient.name == "iron") {
                    newNutrients.iron = nutrient;
                }
                else if (nutrient.name == "calcium") {
                    newNutrients.calcium = nutrient;
                }
                else if (nutrient.name == "potassium") {
                    newNutrients.potassium = nutrient;
                }
                else if (nutrient.name == "phosphorus") {
                    newNutrients.phosphorus = nutrient;
                }
                else {
                }
            }
            NutritionFacts nf;
            RBT.search(element.first)->nutrition = nf;
        }
    }


};



