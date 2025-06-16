#include "user.h"


// Static member initialization
int User::lastAssignedID = 0;

// Default constructor
User::User(): fname(""), lname(""), password(""), email(""), id(0) {}

// Parameterized constructor
User::User(const string& fname, const string& lname, const string& password, const string& email) {
    this->fname = fname;
    this->password = password;
    this->lname = lname;
    this->email = email;
    lastAssignedID++;
    id = lastAssignedID;
    username = fname + " " + lname;
}

// Getter for username
string User::getUsername() const {
    return username;
}

// Getter for password
string User::getPassword() const {
    return password;
}

// Getter for email
string User::getEmail() const {
    return email;
}

// Getter for ID
int User::getID() const {
    return id;
}

// Setter for password
void User::setPassword(const string& password) {
    this->password = password;
}

// Method to view appointments
void User::viewAppointments(vector<Appointment>* appointments) {
    if(appointments->empty()) {
        cout << "There are no booked appointments!\n";
        return;
    }
    cout << "List of Confirmed Appointments:" << endl;
    for(size_t i = 0; i < appointments->size(); ++i) {
        cout << i + 1 << ". ";
       (*appointments)[i].display();
    }
}

// Method to get appointments of a user
vector<Appointment>* User::getAppointments(const set<Appointment>& appointments) const {
    vector<Appointment>* userAppointments = new vector<Appointment>();
    for(const auto& appointment : appointments) {
        if(appointment.getPatientName() == this->getUsername() || appointment.getDoctorName() == this->getUsername()) {
            userAppointments->push_back(appointment);
        }
    }
    return userAppointments;
}

// Method to cancel an appointment
void User::cancelAppointment(set<Appointment>& appointments) {
    vector<Appointment>* bookedAppointments = this->getAppointments(appointments);
    if(bookedAppointments->empty()) {
        cout << "User has no booked appointments!\n";
        return;
    }
    this->viewAppointments(bookedAppointments);
    int choice;
    validateInputType(choice);
    while(choice < 1 || choice > (int)bookedAppointments->size()) {
        cout << "Invalid choice to delete, Kindly select a valid option: ";
        cin >> choice;
    }
    const Appointment appointment = (*bookedAppointments)[choice - 1];
    auto it = appointments.find(appointment);
    if(it != appointments.end()) {
        appointments.erase(it);
        cout << "Appointment deleted successfully!" << endl;
    } else {
        cout << "Appointment not found." << endl;
    }
    delete bookedAppointments;
}

// Method to print user information
void User::print() const {
    cout << username << endl;
}