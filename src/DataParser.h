#ifndef DSAPROJECT3_NEW_DATAPARSER_H
#define DSAPROJECT3_NEW_DATAPARSER_H
#include <iostream>
#include <unordered_map>
#include <fstream>

class DataParser {
private:
    std::unordered_map<int, std::string> nutrients;
    std::fstream curr_file;

public:
    void readAllFile();
    void readNutrient();
};



#endif //DSAPROJECT3_NEW_DATAPARSER_H
