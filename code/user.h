#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "appointment.h"
#include "helpers.h"

using namespace std;

class User {
protected:
    string fname, lname, password, email, username;
    int id;
    static int lastAssignedID;

public:
    // Constructors
    User();
    User(const string& fname, const string& lname, const string& password, const string& email);

    // Getter methods
    string getUsername() const;
    string getPassword() const;
    string getEmail() const;
    int getID() const;

    // Setter method
    void setPassword(const string& password);

    // Other methods
    void viewAppointments(vector<Appointment>* appointments);
    void cancelAppointment(set<Appointment>& appointments);
    vector<Appointment>* getAppointments(const set<Appointment>& appointments) const;
    void print() const;
};

#endif // USER_H