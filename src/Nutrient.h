#pragma once
#include <string>
#include<map>

using namespace std;

class Nutrient {
public:
    string name;
    string unit_name;
    double amount;
    int dailyValue;

    Nutrient(const string& name, const string& unit_name, double amount, int dailyValue)
            : name(name), unit_name(unit_name), amount(amount), dailyValue(dailyValue) {}
};
