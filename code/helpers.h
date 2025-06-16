#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <regex>
#include "appointment.h"

using namespace std;

template<typename T>
bool login(string username, string password, unordered_map<string, T>& objectsByName, int& entry) {
    if (objectsByName.find(username) != objectsByName.end()) {
        if (objectsByName[username].getPassword() == password) {
            cout << "Login successful!" << endl;
            return true;
        } else {
            cout << "Invalid password. Login failed." << endl;
            entry = 1;
            return false;
        }
    } 
    cout << "Account not found. Please register first." << endl;
    entry = 3;
    return false;
}

// Function to check if the input string matches the date format "YYYY-MM-DD"
inline bool  isValidDateFormat(const std::string& input) 
{
    std::regex pattern("\\d{4}-\\d{2}-\\d{2}"); // Regular expression for date format
    return std::regex_match(input, pattern);
}

// Function to print the availability of a doctor on a specific date
inline void  printAvailability(const unordered_map<int, string>& availabilityMap, const string& date) 
{
    // Print availability
    cout << "Doctor's availability on " << date << ":" << endl;
    for(const auto& entry : availabilityMap) {
        std::cout << "Hour " << entry.first << ": " << entry.second << std::endl;
    }
}

// Template function to validate input type
template<typename T>
inline void validateInputType(T& selection) 
{
    while (true) {
        cout << "Please select an option from the menu/list: ";
        cin >> selection;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore any remaining characters
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input." << endl;
        } else {
            break;
        }
    }
}

// Specialized template for char validation
template<> inline void validateInputType <char>(char& selection) 
{
    string input;
    while (true) {
        cout << "Do you want to try again? (y/n): ";
        cin >> input;
        if (input.size() == 1) {
            selection = input[0];
            break;
        } else {
            cout << "Invalid input. Please enter a single character." << endl;
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining characters
        }
    }
}

#endif