#include "doctor.h"
#include <iomanip>

// Default constructor for Doctor class
Doctor::Doctor() : User() {
    // Initialize working hours with default values (0, 0)
    workingHours.push_back(0);
    workingHours.push_back(0);
}

// Parameterized constructor for Doctor class
Doctor::Doctor(const string& fname, const string& lname, const string& password, const string& email,
    const int startHour, const int endHour, const string& specialization)
    : User(fname, lname, password, email), specialization(specialization) {
        // Initialize working hours with provided startHour and endHour
        workingHours.push_back(startHour);
        workingHours.push_back(endHour);
}

// Accessor method to retrieve the specialization of the doctor
string Doctor::getSpecialization() const {
    return specialization;
}

// Accessor method to retrieve the working hours of the doctor
vector<int> Doctor::getWorkingHours() const {
    return workingHours;
}

// Method to get the availability of the doctor on a specific date
unordered_map<int, string>* Doctor::getAvailabilityOnDate(const set<Appointment>& appointments, const string& date) {
    // Create a new map to store the availability
    unordered_map<int, string>* availabilityMap = new unordered_map<int, string>();

    // Initialize availability for all working hours as "Available"
    for(int hour = workingHours[0]; hour <= workingHours[1]; ++hour) {
        (*availabilityMap)[hour] = "Available";
    }

    // Check appointments for the given date and update availability
    for(const Appointment& appointment : appointments) {
        if(appointment.getDoctorName() == getUsername() && appointment.getDate() == date) {
            // Mark the appointment hour as "Booked"
            int appointmentHour = stoi(appointment.getHour()); // Convert appointment hour from string to int
            (*availabilityMap)[appointmentHour] = "Booked";
        }
    }

    return availabilityMap;
}

// Method to print doctor details
void Doctor::print() const {
    // Output doctor's username, specialization, and working hours
    cout << "Doctor: " << username << ", Specialization: " << specialization << ", Working hours: From " << setfill('0') 
    << std::setw(2) << to_string(workingHours[0]) << " to " << setfill('0') << std::setw(2) << workingHours[1] <<  endl;
}