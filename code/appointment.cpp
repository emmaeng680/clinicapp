// Include the necessary library for setw and setfill
#include <iomanip>
#include "appointment.h"
using namespace std;

// Constructor definition for the Appointment class
Appointment::Appointment(const string& date, const string& time, string doctorName, string patientName)
    : date(date), hour(time), doctorName(doctorName), patientName(patientName){}

// Method to get the date of the appointment
string Appointment::getDate() const {
    return date;
}

// Method to get the hour of the appointment
string Appointment::getHour() const {
    return hour;
}

// Method to get the name of the doctor for the appointment
string Appointment::getDoctorName() const {
    return doctorName;
}

// Method to get the name of the patient for the appointment
string Appointment::getPatientName() const {
    return patientName;
}

// Method to display the details of the appointment
void Appointment::display() const{
    // Display the appointment details with proper formatting
    cout << "Date: " << date << ", Hour: " << setfill('0') << std::setw(2) << hour 
         << ", Doctor: " << doctorName << ", Patient: " << patientName << endl;
    }