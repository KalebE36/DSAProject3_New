#include <string>
#include <map>

//  This class will represent the data structure for a single food item, including its nutritional information, servings, and selection details. 
// Nutrition Data could also be moodified to be a nested struct 


class FoodItem {
private:
    int id;
    std::string name;
    std::map<std::string, double> nutrients;
    std::map<std::string, std::pair<double, std::string>> servings; // Pair of weight and description

public:
    FoodItem(){name = "NULL"; id = 0;}
    FoodItem(int id, std::string name) {this->id = id; this->name = name; }

    /*
    void setSelectedQuantity(int quantity);
    void setSelectedWeight(const std::string& weight);
     */

    std::string getName() {return name;}
    int getID() {return id;}


};
