#pragma once
#include <string>
#include<map>

using namespace std;

class Nutrient {
public:
    string name;
    double amount;
    int dailyValue;

    Nutrient(const string& name, double amount, int dailyValue)
            : name(name), amount(amount), dailyValue(dailyValue) {}
};
