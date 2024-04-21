#include <string>
#include <map>

//  This class will represent the data structure for a single food item, including its nutritional information, servings, and selection details. 
// Nutrition Data could also be moodified to be a nested struct 


class FoodItem {
private:
    struct NUTRIENT_DATA {
        float amount_1003;
        float amount_1004;
        float amount_1005;
    };

    int id;
    std::string name;
    std::map<std::string, double> nutrients;
    std::map<std::string, std::pair<double, std::string>> servings;// Pair of weight and description
    NUTRIENT_DATA ND;

public:
    FoodItem(){name = "NULL"; id = 0; ND = {};}
    FoodItem(int id, std::string name) {this->id = id; this->name = name; }

    /*
    void setSelectedQuantity(int quantity);
    void setSelectedWeight(const std::string& weight);
     */

    std::string getName() {return name;}
    int getID() {return id;}
    void setID(int& id) {this->id = id;}
    void setNutrients(const float& amount_1003, const float& amount_1004, const float& amount_1005) {
        ND = {amount_1003, amount_1004, amount_1005};
    }

    float getNutrient_1003() {return ND.amount_1003;}
    float getNutrient_1004() {return ND.amount_1004;}
    float getNutrient_1005() {return ND.amount_1005;}


};
