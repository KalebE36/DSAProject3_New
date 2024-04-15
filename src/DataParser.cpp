#include "DataParser.h"
#include <sstream>

void DataParser::readAllFile() {

}

void DataParser::readFoodItems() {
    curr_file.open("../db/food.csv");
    if(!curr_file.is_open()) {
        std::cout << "Error opening food.csv" << std::endl;
        exit;
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


void DataParser::readNutrient() {
    curr_file.open("../db/nutrient.csv");
    if(!curr_file.is_open()) {
        std::cout << "Error opening file" << std::endl;
        exit;
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
        std::cout << "Name: " <<element.first << ", ID: " << element.second << std::endl;
    }
}