#ifndef PATIENT_H
#define PATIENT_H

#include "doctor.h"
#include "appointment.h"
// #include "helpers.h"

using namespace std;

class Patient : public User {
public:
    // Constructors
    Patient();
    Patient(const string& fname, const string& lname, const string& password, const string& email);

    // Methods
    vector<Doctor>* searchDoctor(unordered_map<string, Doctor>& doctorsByName, string query);
    void bookAppointment(unordered_map<string, Doctor>& doctorsByName, set<Appointment>& appointments);
};

#endif // PATIENT_H