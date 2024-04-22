# DSAProject3_New
NutriCrunchTeam 
NutritiousDB -	Food Nutritional Database

I.	Overview
This console application manages a large dataset of food items and their nutritional information, sourced from the USDA FoodData Central. It utilizes a Red Black Tree and a Hash Table for efficient retrieval and manipulation of food data, demonstrating the performance of these custom data structures.


II.	Project Structure and Files
src/: Contains all source files for the application.
db/: Directory for storing CSV datasets. (Note: Must be created manually and filled with data files from USDA FDC).

         main.cpp: Entry point of the application, handling user interactions and system initialization.
         RedBlackTree.h, HashTable.h: Templated classes that implement the custom Red Black Tree and Hash Table data structures.
         FoodItem.h, Nutrient.h, Nutrients.h, FoodDatabase.h: Define the classes that manage the nutritional data.
         DataParser.h: Handles parsing of CSV files and populating data structures.


III.	Data Retrieval
Datasets need to be manually downloaded due to their large size and stored in the db/ directory under the project root. These CSV files can be downloaded from the USDA FoodData Central.


IV.	Classes and Functionalities

         Nutrient: Represents a single nutrient, including its name, unit, amount, and daily value.
         
         Nutrients: Manages a collection of Nutrient objects, providing functionality to sort and access nutrient data.
         
         FoodItem: Models a food item with an ID, name, description, and associated Nutrients, and other class member variables for future potential features. 
         
         FoodDatabase: Acts as the central database, utilizing RedBlackTree and HashTable for efficient data retrieval.
         
         DataParser: Responsible for parsing the CSV files and initializing the FoodDatabase with parsed data.


V.	Installation and Setup
Prerequisites
A C++ development environment such as Visual Studio or GCC.
 
  Setup Instructions
  1.	Clone the repository:
    git clone https://github.com/KalebE36/DSAProject3_New.git
  cd DSAProject3_New
  
  2.	Prepare the data:
  Download the required CSV files from USDA FDC and place them in the db/ directory.
    https://fdc.nal.usda.gov/fdc-datasets/FoodData_Central_branded_food_csv_2023-10-26.zip
  
  4.	Build the Application:
  Open the project in your C++ development environment.
  Build the project using the native build tools (e.g., Makefile, Visual Studio solution).
  
  5.	Run the application:
  Execute the built application through your development environment or from the command line.


Example Usage
Welcome to the Food Nutritional Database
1. Search Nutrition Facts
2. Compare Two Foods
3. Nutrient Ranking Tool 
0. Exit
Enter your choice: 

Future Enhancements
Integration of the SFML library for a graphical user interface.
Additional features such as user accounts, more detailed search filters, and interactive nutritional charts.

Contributing
Contributions are welcome. Please fork the repository, make your changes, and submit a pull request with your improvements.

License
This project is licensed under the MIT License - see the LICENSE.md file for details.
