#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include "DataParser.h"

/* We can change this to have an input in main to show where csv files are */
/* We would just add a parameter */
void DataParser::read_food_nutrients() {
    curr_file.open("../db/copied_food_nutrient.csv");
    if(!curr_file.is_open()) {
        std::cout << "Error opening copied_food_nutrient.csv" << std::endl;
        std::exit(1);
    }
    std::string line;
    bool first = true;
    int count = 0;
    while(getline(curr_file, line)) {
        std::stringstream ss(line);
        std::string id, amount_1003, amount_1004, amount_1005;
        getline(ss, id, ',');
        getline(ss, amount_1003, ',');
        getline(ss, amount_1004, ',');
        getline(ss, amount_1005, ',');

        /*
        id.erase(remove(id.begin(), id.end(), '"'), id.end());
        amount_1003.erase(remove(amount_1003.begin(), amount_1003.end(), '"'), amount_1003.end());
        amount_1004.erase(remove(amount_1004.begin(), amount_1004.end(), '"'), amount_1004.end());
        amount_1005.erase(remove(amount_1005.begin(), amount_1005.end(), '"'), amount_1005.end());
        */
        FoodItem item;
        if(!first) {
                int id_num = stoi(id);
                float amount_1003f = stof(amount_1003);
                float amount_1004f = stof(amount_1004);
                float amount_1005f = stof(amount_1005);
                item.setID(id_num);
                item.setNutrients(amount_1003f, amount_1004f, amount_1005f);
                 nutrients[id_num] = item;
        } else {
            first = false;
        }
        std::cout << count << std::endl;
        ++count;
    }
    curr_file.close();
}

void DataParser::readAllFile() {

}

void DataParser::readFoodItems() {
    curr_file.open("../db/food.csv");
    if(!curr_file.is_open()) {
        std::cout << "Error opening food.csv" << std::endl;
        std::exit(1);
    }

    std::string line;
    int count = 0;
    while(getline(curr_file, line)) {
        std::stringstream ss(line);
        std::string id, data_type, name, food_cat_id, publ_date, market, trade, mic_dat;
        getline(ss, id, ','); getline(ss, data_type, ','); getline(ss, name, ','); getline(ss, food_cat_id, ','); getline(ss, publ_date, ',');
        getline(ss, market, ','); getline(ss, trade, ','); getline(ss, mic_dat, ',');

        id.erase(remove(id.begin(), id.end(), '"'), id.end());
        name.erase(remove(name.begin(), name.end(), '"'), name.end());


        if(count > 0) {
            FoodItem item(stoi(id), name);
            std::cout << "Name of Food Item: " << item.getName() << ", Food Item ID: " << item.getID() << std::endl;

        }
        ++count;
    }
    curr_file.close();
}

/*
void DataParser::readNutrient() {
    curr_file.open("../db/nutrient.csv");
    if(!curr_file.is_open()) {
        std::cout << "Error opening file" << std::endl;
        std::exit(1);
    }

    std::string line;
    while(getline(curr_file, line)) {
        std::stringstream ss(line);
        std::string id, name, unit_name, nutrient_nbr_str, rank_str;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, unit_name, ',');
        getline(ss, nutrient_nbr_str, ',');
        getline(ss, rank_str, ',');

        name.erase(remove(id.begin(), id.end(), '"'), id.end());
        id.erase(remove(id.begin(), id.end(), '"'), id.end());

        int id_num;
        try {
            id_num = stoi(id);
            nutrients[name] = id_num;
        } catch (...) {
            std::cout << "Error converting id to integer: " << id << std::endl;
            continue; // Skip this row if id cannot be converted to integer
        }

    }
    curr_file.close();
}

void DataParser::printNutrients() {
    for(auto& element : nutrients) {
        std::cout << "ID: " <<element.first << ", Num_1003: " << element.second.getNutrient_1003() << std::endl;
    }
}*/