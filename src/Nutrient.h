#pragma once
#include <string>
#include<map>

using namespace std;

class Nutrient {
public:
    string name;
    double amount;
    double dailyValue;

    Nutrient(string name, double amount, double dailyValue)
        : name(name), amount(amount), dailyValue(dailyValue) {}
};
