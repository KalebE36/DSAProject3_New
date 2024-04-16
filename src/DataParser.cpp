#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include "DataParser.h"

std::unordered_map<int, NutrientData> read_food_nutrients(const std::string& filename) {
    std::unordered_map<int, NutrientData> nutrients;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return nutrients;
    }

    // Read and discard the header row
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> tokens;

        while (std::getline(ss, cell, ',')) {
            tokens.push_back(cell);
        }

        if (tokens.size() >= 4) {
            try {
                int fdc_id = std::stoi(tokens[0]);
                float amount_1003 = tokens[1].empty() ? 0.0f : std::stof(tokens[1]);
                float amount_1004 = tokens[2].empty() ? 0.0f : std::stof(tokens[2]);
                float amount_1005 = tokens[3].empty() ? 0.0f : std::stof(tokens[3]);
                nutrients[fdc_id] = { amount_1003, amount_1004, amount_1005 };
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Error: Invalid argument in line \"" << line << "\": " << e.what() << std::endl;
            }
            catch (const std::out_of_range& e) {
                std::cerr << "Error: Out of range in line \"" << line << "\": " << e.what() << std::endl;
            }
        }
    }

    file.close();
    return nutrients;
}