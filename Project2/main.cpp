// Program that reads a csv file and loads into data structure
//  Project 2
//  Created by Jermaine Wiggins on 2/21/25.

#include <iostream>
#include <cctype>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <stdexcept>
#include "dataStructureFunctions.h"

using namespace std;

// main
int main(int argc, const char * argv[]) {
    
    const string FILENAME = "SNHU.csv";// csv file
    vector <Course> courses; // struct to hold all course info from csv
    set <string> allCourses; // used to validate if prereqs are valid
    fstream inFile; // read file
    int userInput = 0; // get user input for menu
    string search = ""; // user input to
    
    do {
        printMenu();
        getUserInput(userInput);
        menuInput(inFile, FILENAME, userInput, search, courses, allCourses);
        
    }while (userInput != 9); // controls program flow
    
    return 0;
}

