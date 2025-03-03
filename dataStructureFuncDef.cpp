// Project 2 function definitions
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

// Function definitions

// opens file
void openFile(fstream& inFile, const string& FILENAME) {
    inFile.open(FILENAME);
    if(!inFile.is_open()) {
        cerr << "Error opening " << FILENAME << endl;
        inFile.close();// close file if error
        exit(1);
    }
}

// load course names into set used to validate prereqs
void loadSet (fstream& inFile, const string& FILENAME, set<string>& allCourses) {
    openFile(inFile, FILENAME);

    string line; // store line
    string code; // store course code
    stringstream courseInfo(line); // helps extract course code
    
    // copy course code to set
    while (getline(inFile, line)) {
        stringstream courseInfo(line);
        getline(courseInfo, code, ',');
        
        if (!code.empty())
        allCourses.insert(code);
    }
    // confirm operation is successful
    cout << FILENAME << " loaded into set" << endl;
    inFile.close();
}

// checks if course name is valid before adding to structure
bool validateCourse(const Course& newCourse) {
    if ((newCourse.courseCode.empty() && !isspace(newCourse.courseCode[0])) || (newCourse.courseName.empty() && !isspace(newCourse.courseName[0]))) {
        cout << "Not a valid file, name or code missing" <<endl;
        return false;
    }
    return true;
}

// check if prereqs are in file as a course
bool validatePrereq(const set<string>& allCourses, Course& newCourse) {
   
    // if size of prereqs vector is 0 skip and return
    if (newCourse.preReq.size() > 0) {
        
        // check if prereq in all courses set
        for (const auto& prereq : newCourse.preReq) {
            if (allCourses.find(prereq) == allCourses.end()) {
                
                // if not in set print error message
                cout << "Prerequisite " << prereq << " not found in course codes." << endl;
                return false ;
            }
            
        }
        
    }
    return true;
}

// copy course object to vector
void copyToVector(vector<Course>& courses, Course& newCourse) {
    
    courses.push_back(newCourse);
}

// checks if file is valid
void checkReadFile(fstream& inFile, const string& FILENAME, set<string>& allCourses, vector<Course>& courses) {
    loadSet(inFile, FILENAME, allCourses); // loads all course codes into set for validation checks
    openFile(inFile, FILENAME); // opens file
    
    string line; // used to store lines of csv file
    
    while (getline(inFile, line)) {
        Course newCourse; // create new course object
        string prereq; // store prereqs before adding to vector in object
        stringstream courseInfo(line); // helps seperate line
        
        // read a line up to ,
        getline(courseInfo, newCourse.courseCode, ',');
        getline(courseInfo, newCourse.courseName, ',');

        // read all prereqs
        while (getline(courseInfo, prereq, ',')) {
            
            // if any add to vecotr in object
            if (!prereq.empty() && !isspace(prereq[0])) {
                newCourse.preReq.push_back(prereq);
            }
        }
        
        // check if course name is valid name and course code
        if (!validateCourse(newCourse)) {
            inFile.close();
            return; // invalid file if false
        }
        
        // check if prereqs in all course set
        if (!validatePrereq(allCourses, newCourse)) {
            inFile.close();
            return; // invalid file if false
        }
        
        copyToVector(courses, newCourse);
        
    }
    cout << FILENAME << " is loaded into Data structure" << endl;
    cout << endl;
    inFile.close();
    
}

// helps sort function in two halves
int partition(vector<Course>& courses, int low, int high){
    
    // stores vector first and last index
    int begin = low;
    int end = high;
    
    // vector midpoint
    int mid = low + (high - low) / 2;
    
    // determine pivot
    string pivot = courses[mid].courseCode;
    
    
    bool done = false;
    while (!done) {
        // shift begin so its before pivot
        while (courses[begin].courseCode < pivot) {
            begin++;
        }
        // shift end so its after pivot
        while (pivot < courses[end].courseCode) {
            end--;
        }
        
        // if begin and end cross end loop
        if (begin >= end) {
            done = true;
        }
        // swap begin and emd to move to correct position
        else {
            swap(courses[begin], courses[end]);
            begin++;
            end--;
        }
    }
    return end;
}

// quicksort recurvively
void quickSort(vector<Course>& courses, int low, int high) {
    
    int midpoint = 0; // used to partition
    
    // base case
    if (low >= high) {
        return;
    }
    
    midpoint = partition(courses, low, high);
    
    // sort upper bound
    quickSort(courses, low, midpoint);
    
    // sort lower bound
    quickSort(courses, midpoint + 1, high);
}

// print courses after sorting
void printSortedCourses(vector<Course>& courses) {
    quickSort(courses, 0, courses.size() - 1);
    
    // print course info
    for (int i = 0; i < courses.size(); i++) {
        cout << courses[i].courseCode << ": " << courses[i].courseName << " | ";
        
        // print prereqs if any
        for (int j = 0; j < courses[i].preReq.size(); j ++) {
            cout << courses[i].preReq[j];
            
            if (j < courses[i].preReq.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl; // print new line between courses
    }
    cout << endl; // print new line
    
}

// validates search user input
bool checkIfSearchValid(string& search, set<string>& allCourses) {
    
    // course not found print error message
    if (allCourses.find(search) == allCourses.end()) {
        cout << "Course doesn't exist in CS program." << endl;
        cout << "List of valid courses" << endl;
        
        // prints valid courses user can see
        for (const auto& course : allCourses) {
            cout << course << endl;
            }
        cout << endl;
        return false;
    }
    return true;
}

//searches for course after validating
void searchFor(vector<Course>& courses, set<string>& allCourses, string& search) {
    
    // finds course and prints info
    for ( int i = 0; i < courses.size(); i++) {
        if (search == courses[i].courseCode) {
            cout << courses[i].courseCode << ": " << courses[i].courseName << endl;
            
            // prints prereqs if any
            if ( courses[i].preReq.size() > 0) {
                cout << "Prerequistes: ";
            }
            for (int j = 0; j < courses[i].preReq.size(); j ++) {
                cout << courses[i].preReq[j];
                if (j < courses[i].preReq.size() - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
            break;
        }
        
    }
    
}

// prints menu
void printMenu() {
    // Variables
    const int BORDER_LENGTH = 35; // length of borders
    const char BORDER_CHAR = '*'; // char used to print border
    const string MENU_NAME = "Welcome to ABCU CS Course Planner"; // app name
    string border(BORDER_LENGTH, BORDER_CHAR); // string to print border
    
    
    // Print Menu
    cout << border << endl;
    cout << setw(BORDER_LENGTH - static_cast<int>(MENU_NAME.size()) / 2) << MENU_NAME << endl;
    cout << border << endl;
    cout << "Press 1 To load csv file" << endl;
    cout << "Press 2 Sort and print courses" << endl;
    cout << "Press 3 To search for a course" << endl;
    cout << "Press 9 To exit" << endl;
}

//validate user input
void getUserInput(int& userInput) {
    cin.exceptions(ios::failbit | ios::badbit); // sets exception handling for cin
    
    cout << "Enter your selection: ";
    do {
        // try catch block for input validation
        try {
           // get user input
            cin >> userInput;
            
            // throws out of bound exception
            if (userInput < 1 || (userInput > 3 && userInput != 9)){
                throw out_of_range("Please enter a int between 1 and 3 or 9 to exit");
            }
            
        }
        // catches mismatch exceptions
        catch (ios_base::failure&) {
            cin.clear(); // clear buffer
            cin.ignore(100, '\n'); // ignores next 100 char up to new line
            
            cout << "Please enter an interger: ";
        }
        // catch out of bound exception
        catch (out_of_range) {
            cin.ignore(100, '\n'); // ignores next 100 char up to new line
            
            cout << "Please enter a int between 1 and 3 or 9 to exit: ";
        }
    }while (userInput < 1 || (userInput > 3 && userInput != 9 ));
    cout << endl;
}

// force search to upper for easier matches
void forceCapLock(string& search) {
    for (auto& letters : search) {
        letters = toupper(letters);
    }
}

//case switch
void menuInput(fstream& inFile, const string& FILENAME, int& userInput, string& search, vector<Course>& courses, set<string>& allCourses) {
    
    switch (userInput) {
        
            // load file
        case 1:
            checkReadFile(inFile, FILENAME, allCourses, courses);
            break;
           // sort and print all courses
        case 2:
            if (courses.size() < 1) {
                cout << "Enter option 1 to load courses." << endl;
            }
            printSortedCourses(courses);
            
            break;
           // search for specific course
        case 3:
            if (courses.size() < 1) {
                cout << "Enter option 1 to load courses." << endl;
            }
            do {
                cout << "Enter a course to search for: ";
                cin >> search;
                forceCapLock(search);
            } while (!checkIfSearchValid(search, allCourses));
            searchFor(courses, allCourses, search);
            break;
            // exit
        case 9:
            cout << "Exiting Program." << endl;
            break;
        
        default:
            break;
    }
}

