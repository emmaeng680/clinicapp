#ifndef DOCTOR_H
#define DOCTOR_H

#include <unordered_map>
#include <vector>
#include "user.h"

using namespace std;

class Doctor : public User {
private:
    vector<int> workingHours; // Stores the working hours of the doctor
    string specialization;    // Stores the specialization of the doctor

public:
    // Default constructor
    Doctor();
    
    // Parameterized constructor
    Doctor(const string& fname, const string& lname, const string& password, const string& email,
        const int startHour, const int endHour, const string& specialization);
    
    // Accessor method to retrieve the specialization of the doctor
    string getSpecialization() const;
    
    // Accessor method to retrieve the working hours of the doctor
    vector<int> getWorkingHours() const;
    
    // Method to get the availability of the doctor on a specific date
    unordered_map<int, string>* getAvailabilityOnDate(const set<Appointment>& appointments, const string& date);
    
    // Method to print doctor details
    void print() const;
};

#endif // DOCTOR_H