#include "patient.h"

// Default constructor for Patient class
Patient::Patient() : User() {}

// Parameterized constructor for Patient class
Patient::Patient(const string& fname, const string& lname, const string& password, const string& email)
    : User(fname, lname, password, email) {}

// Method to search for doctors based on name or specialization
vector<Doctor>* Patient::searchDoctor(unordered_map<string, Doctor>& doctorsByName, string query) {
    // Create a vector to store matching doctors
    vector<Doctor>* matchingDoctors = new vector<Doctor>();

    // Iterate through doctors to find matching ones
    for(const auto& doctor : doctorsByName) {
        if(doctor.second.getUsername().find(query) != string::npos ||
            doctor.second.getSpecialization().find(query) != string::npos) {
            matchingDoctors->push_back(doctor.second);
        }
    }

    return matchingDoctors;
}

// Method to book an appointment with a doctor
void Patient::bookAppointment(unordered_map<string, Doctor>& doctorsByName, set<Appointment>& appointments) {
    if(doctorsByName.empty()) {
        cout << "There are no doctors in the system!\n";
        return;
    }

    string doctorSearch;
    cout << "Search for a doctor by name or specialization: ";
    cin.ignore();
    getline(cin, doctorSearch);

    vector<Doctor>* matchingDoctors = this->searchDoctor(doctorsByName, doctorSearch);

    if(matchingDoctors->empty()) {
        cout << "No matching doctors found. Here is a list of all available doctors:" << endl;
        int index = 1;
        for(const auto& doctorPair : doctorsByName) {
            cout << index << ". ";
            doctorPair.second.print(); // Assuming there's a print() function in the Doctor class.
            index++;
        }
    } else {
        cout << "Matching Doctors:" << endl;
        for(size_t i = 0; i < matchingDoctors->size(); ++i) {
            cout << i + 1 << ". ";
            (*matchingDoctors)[i].print();
        }
    }

    int doctorChoice;
    cout << "Select a doctor by entering its corresponding number: ";
    cin >> doctorChoice;

    // Validate the doctor choice
    while(doctorChoice < 1 || (doctorChoice > (int)matchingDoctors->size() && !matchingDoctors->empty())) {
        cout << "Invalid choice. Please select a valid number: ";
        cin >> doctorChoice;
    }
    
    Doctor chosenDoctor;
    if(matchingDoctors->empty()) {
        // Select from all doctors
        auto it = doctorsByName.begin();
        advance(it, doctorChoice - 1);
        chosenDoctor = it->second;
    } else {
        // Select from matching doctors
        chosenDoctor = (*matchingDoctors)[doctorChoice - 1];
    }
    delete matchingDoctors;

    string date;
    bool isValidDate = false;
    bool attempted = false;
    try {
        while(!isValidDate) {
            if (!attempted){
                cout << "Enter date for appointment(yyyy-mm-dd): ";
                cin >> date;
                attempted = true;
            }
            isValidDate = isValidDateFormat(date);
            if(!isValidDate) {
                char choice;
                cout << "Invalid date format.\n";
                validateInputType<char>(choice);
                switch(choice) {
                    case 'y': {
                        cout << "Enter date in valid format: ";
                        cin >> date;
                        break;
                    }
                    case 'n': {
                        throw("Appointment booking cancelled");
                    }
                    default: 
                        cout << "Invalid selection, sending you to landing page.\n";
                        throw("Appointment booking cancelled");
                }
            }
        }
        // Display chosen doctor's availability on date
        unordered_map<int, string>* doctorAvailabilityOnDate = chosenDoctor.getAvailabilityOnDate(appointments, date);
        printAvailability(*doctorAvailabilityOnDate, date);

        // Enter available hour or go back
        int appointmentHour;
        bool isValidHour = false;
        while(!isValidHour) {
            cout << "Enter only hour number...\n";
            validateInputType(appointmentHour);
            auto it = doctorAvailabilityOnDate->find(appointmentHour);
            isValidHour = (it != doctorAvailabilityOnDate->end() && it->second != "Booked");
            if(!isValidHour) {
                char choice;
                cout << "Selected hour is booked or unavailable\n";
                validateInputType<char>(choice);
                switch(choice) {
                    case 'y': {
                        cout << "Enter a valid appointment hour: ";
                        cin >> appointmentHour;
                        break;
                    }
                    case 'n': {
                        throw("Appointment booking cancelled");
                    }
                    default: 
                        cout << "Invalid selection, sending you to landing page.\n";
                        throw("Appointment booking cancelled");
                }
            }
        }
        Appointment newAppointment(date, to_string(appointmentHour), chosenDoctor.getUsername(), this->getUsername());
        appointments.insert(newAppointment);
        cout << "Appointment booked successfully!" << endl;
    } catch(char const*  errorMsg) {
        cout << errorMsg << endl;
    }
}