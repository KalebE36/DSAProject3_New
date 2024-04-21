#pragma once
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include "FoodItem.h"
#include "Nutrient.h"
#include "FoodDatabase.h"
#include "RedBlackTree.h"
#include "HashTable.h"

using namespace std;
/* This is a very general idea of a data parser that we could use for csv files */
class DataParser {
private:
    RedBlackTree<int, FoodItem> RBT;
    HashTable<int, FoodItem> hashTable;
    unordered_map<int, pair<string, string>> nutrientIDM;
    unordered_map<int, vector<Nutrient>> nutrientPF;
    fstream currFile;


public:

    void parseFoodCSV() {
        currFile.open("../db/food.csv");
        if (!currFile.is_open()) {
            std::cout << "Error opening food.csv" << std::endl;
            std::exit(1);
        }

        std::string line;
        int count = 0;
        while (getline(currFile, line) && (count < 200001)) {
            std::stringstream ss(line);
            std::string id, data_type, name, food_cat_id, publ_date, market, trade, mic_dat;
            getline(ss, id, ','); getline(ss, data_type, ','); getline(ss, name, ','); getline(ss, food_cat_id, ','); getline(ss, publ_date, ',');
            getline(ss, market, ','); getline(ss, trade, ','); getline(ss, mic_dat, ',');

            // Remove quotes from fields
            id = id.substr(1, id.size() - 2);
            name = name.substr(1, name.size() - 2);

            if (count > 0) {
                FoodItem item;
                item.id = std::stoi(id);
                item.name = std::move(name); 
                RBT.insert(item.id, item);
                hashTable.insert(item.id, item);
            }
            ++count;
        }
        currFile.close();
    }

    void parseBrandedFoodCSV() {
        currFile.open("../db/branded_food.csv");
        if (!currFile.is_open()) {
            cout << "Error opening food.csv" << endl;
            exit(1);
        }

        string line;
        int count = 0;
        while (getline(currFile, line) && (count < 200001)) {
            stringstream ss(line);
            string id, branOwner, branName, subBrand, gtin, description, notS, servSize, servSizeUnit, hhServing, bfoodCat, source, packageWeight, mD, aD, market, dD, pSC, tC, sD;
            getline(ss, id, '"'); getline(ss, id, '"'); getline(ss, branOwner, '"'); getline(ss, branOwner, '"'); getline(ss, branName, '"');
            getline(ss, branName, '"'); getline(ss, subBrand, '"'); getline(ss, subBrand, '"'); getline(ss, gtin, '"'); getline(ss, gtin, '"');
            getline(ss, description, '"'); getline(ss, description, '"'); getline(ss, notS, '"'); getline(ss, notS, '"'); getline(ss, servSize, '"'); getline(ss, servSize, '"');
            getline(ss, servSizeUnit, '"'); getline(ss, servSizeUnit, '"'); getline(ss, hhServing, '"'); getline(ss, hhServing, '"'); getline(ss, bfoodCat, '"');
            getline(ss, bfoodCat, '"'); getline(ss, source, '"'); getline(ss, source, '"'); getline(ss, packageWeight, '"'); getline(ss, packageWeight, '"');
            getline(ss, mD, '"'); getline(ss, mD, '"'); getline(ss, aD, '"'); getline(ss, aD, '"'); getline(ss, market, '"');
            getline(ss, market, '"'); getline(ss, dD, '"'); getline(ss, dD, '"'); getline(ss, pSC, '"'); getline(ss, pSC, '"');
            getline(ss, tC, '"'); getline(ss, tC, '"'); getline(ss, sD, '"'); getline(ss, sD, '"');

            //description.erase(remove(description.begin(), description.end(), '"'), description.end());
            id.erase(remove(id.begin(), id.end(), '"'), id.end());

            try {
                if (count < 200000) {
                    auto itemH = hashTable.search(std::stoi(id));
                    auto item = RBT.search(std::stoi(id));
                    if (itemH && item) {
                        itemH->description = description;
                        item->description = description;  

                        itemH->servingUnit = std::move(servSizeUnit);
                        itemH->servingSize = std::move(servSize);

                        item->servingUnit = std::move(servSizeUnit);
                        item->servingSize = std::move(servSize);
                    }
                }
            }
            catch (...) {
                continue;
            }
            ++count;
        }
        currFile.close();
    }

    void parseNutrientID() {
        ifstream currFile("../db/nutrient.csv");
        if (!currFile.is_open()) {
            cout << "Error opening file" << endl;
            exit(1);
        }

        string line;
        while (getline(currFile, line)) {
            stringstream ss(line);
            string id, name, unit_name, nutrient_nbr_str, rank_str;
            getline(ss, id, '"');
            getline(ss, id, '"');
            getline(ss, name, '"');
            getline(ss, name, '"');
            getline(ss, unit_name, '"');
            getline(ss, unit_name, '"');
            getline(ss, nutrient_nbr_str, '"');
            getline(ss, nutrient_nbr_str, '"');
            getline(ss, rank_str, '"');
            getline(ss, rank_str, '"');

            // Remove quotes if any from the fields


            int id_num;
            try {
                id_num = stoi(id);
                nutrientIDM[id_num] = { name, unit_name };
            }
            catch (...) {
                continue; // Skip this row if id cannot be converted to an integer
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
        while (getline(currFile, line) && (count < 2500000)) {
            stringstream ss(line);
            string rID, fdcID, nutrientID, amount, dP, derV, min, max, median, loq, footnote, minYear, percDV;
            getline(ss, rID, ','); getline(ss, fdcID, ','); getline(ss, nutrientID, ',');
            getline(ss, amount, ','); getline(ss, dP, ','); getline(ss, derV, ',');
            getline(ss, min, ','); getline(ss, max, ','); getline(ss, median, ',');
            getline(ss, loq, ','); getline(ss, footnote, ','); getline(ss, minYear, ',');
            getline(ss, percDV, ',');

            // Remove quotes from the parsed strings
            fdcID.erase(remove(fdcID.begin(), fdcID.end(), '"'), fdcID.end());
            nutrientID.erase(remove(nutrientID.begin(), nutrientID.end(), '"'), nutrientID.end());
            amount.erase(remove(amount.begin(), amount.end(), '"'), amount.end());
            percDV.erase(remove(percDV.begin(), percDV.end(), '"'), percDV.end());

            try {
                // Check if fdcID exists in the RBT
                if (RBT.search(stoi(fdcID)) && hashTable.search(stoi(fdcID))) {
                    // Assuming nutrientIDM is a map containing nutrient names
                    if (percDV == "") {
                        percDV = "0.0";
                    }
                    pair<string, string> nutrientInfo = nutrientIDM[stoi(nutrientID)];
                    string nutrientName = nutrientInfo.first;
                    string nutrientUnit = nutrientInfo.second;
                    Nutrient nutrient(nutrientName, nutrientUnit, stod(amount), stoi(percDV));
                    nutrientPF[stoi(fdcID)].push_back(nutrient);
                }
            }
            catch (...) {
                continue; // Skip this row if id cannot be converted to integer or if it's not found in RBT
            }

            ++count;
        }
        currFile.close();
    }

    void createNutrients() {
        for (auto& element : nutrientPF) {
            Nutrients newNutrients;
            for (auto& nutrient : element.second) {
                if (nutrient.name == "Energy") {
                    newNutrients.calories = nutrient;
                }
                else if (nutrient.name == "Total lipid (fat)") {
                    newNutrients.totalFat = nutrient;
                }
                else if (nutrient.name == "Fatty acids, total saturated") {
                    newNutrients.saturatedFat = nutrient;
                }
                else if (nutrient.name == "Fatty acids, total trans") {
                    newNutrients.transFat = nutrient;
                }
                else if (nutrient.name == "Cholesterol") {
                    newNutrients.cholesterol = nutrient;
                }
                else if (nutrient.name == "Sodium, Na") {
                    newNutrients.sodium = nutrient;
                }
                else if (nutrient.name == "Carbohydrate, by difference") {
                    newNutrients.totalCarbohydrates = nutrient;
                }
                else if (nutrient.name == "Fiber, total dietary") {
                    newNutrients.fiber = nutrient;
                }
                else if (nutrient.name == "Sugars, Total") {
                    newNutrients.sugar = nutrient;
                }
                else if (nutrient.name == "Sugars, added") {
                    newNutrients.addedSugar = nutrient;
                }
                else if (nutrient.name == "Protein") {
                    newNutrients.protein = nutrient;
                }
                else if (nutrient.name == "vitamin C") {
                    newNutrients.vitaminC = nutrient;
                }
                else if (nutrient.name == "Vitamin D (D2 + D3), International Units") {
                    newNutrients.vitaminD = nutrient;
                }
                else if (nutrient.name == "Iron, Fe") {
                    newNutrients.iron = nutrient;
                }
                else if (nutrient.name == "Calcium, Ca") {
                    newNutrients.calcium = nutrient;
                }
                else if (nutrient.name == "Potassium, K") {
                    newNutrients.potassium = nutrient;
                }
                else if (nutrient.name == "Phosphorus, P") {
                    newNutrients.phosphorus = nutrient;
                }
                else {
                    continue;
                }
                RBT.search(element.first)->nutrients = newNutrients;
                hashTable.search(element.first)->nutrients = newNutrients;
            }
        }
    }

    void loadFiles(FoodDatabase<FoodItem>& db) {
        parseFoodCSV();
        parseBrandedFoodCSV();
        parseNutrientID();
        parseFoodNutrients();
        createNutrients();


        db.setRBT(RBT);
        db.setHashTable(hashTable);

        // Printing each element of the sorted nutrients vector
       // for (const Nutrient& nutrient : sortedNutrients) {
       //     cout << nutrient.name << ": " << nutrient.amount << endl;
        //}
    }
};



