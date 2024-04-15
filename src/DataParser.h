#ifndef DSAPROJECT3_NEW_DATAPARSER_H
#define DSAPROJECT3_NEW_DATAPARSER_H
#include <iostream>
#include <unordered_map>
#include <fstream>
#include "FoodItemData.h"

/* This is a very general idea of a data parser that we could use for csv files */
class DataParser {
private:

    std::unordered_map<std::string, int> nutrients;
    std::fstream curr_file;

public:
    void readAllFile();
    void readNutrient();
    void readFoodItems();
    void printNutrients();
};



#endif //DSAPROJECT3_NEW_DATAPARSER_H
