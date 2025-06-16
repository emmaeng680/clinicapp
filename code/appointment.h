#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <iostream>
#include <string>
using namespace std;

class Appointment{
private:
    string date; // Date of the appointment
    string hour; // Time of the appointment
    string doctorName; // ID of the doctor associated with the appointment
    string patientName; // ID of the patient associated with the appointment

public:
    Appointment(const string& date, const string& time, string doctorName, string patientName);
    string getDate() const;
    string getHour() const;
    string getDoctorName() const;
    string getPatientName() const;
    void display() const;
    // set orders entries so comparator needed
    bool operator < (const Appointment& other) const{
        if (this->date < other.date){
        return true; // If this date is less than other date
    } else if (this->date == other.date){
        // If dates are the same, compare hours
        return this->hour < other.hour;
    } 
        return false; // If this date is greater than or equal to other date
    }
};

#endif // APPOINTMENT_H