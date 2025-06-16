#include "doctor.h"
#include "patient.h"
#include "appointment.h"

using namespace std;

const int CLINIC_TOKEN = 1010;

int main() {
    unordered_map<std::string, Doctor> doctorsByName; // Map to store doctors by their usernames
    unordered_map<std::string, Patient> patientsByName; // Map to store patients by their usernames
    set<Appointment> appointments; // Set to store appointments

    // For testing
    // Doctor doc1("Randy", "Asamoah", "doc1", "rya2005@nyu.edu", 9, 13, "Surgeon");
    // Doctor doc2("Kofi", "Osei", "doc2", "ko05@nyu.edu", 10, 14, "Dentist");
    // Doctor doc3("Ahmed", "Ali", "doc3", "aa23@nyu.edu", 8, 12, "Neurologist");
    // Doctor doc4("Obed", "Atsu", "doc4", "om34@nyu.edu", 14, 18, "Surgeon");
    // doctorsByName[doc1.getUsername()] = doc1;
    // doctorsByName[doc2.getUsername()] = doc2;
    // doctorsByName[doc3.getUsername()] = doc3;
    // doctorsByName[doc4.getUsername()] = doc4;
    // Patient pat1("Kwaaku", "Boamah-Powers", "pat1", "kbp23@gmail.com");
    // patientsByName[pat1.getUsername()] = pat1;
    bool isLoggedIn = false; // Flag to track if a user is logged in
    string quit = "n"; // Flag to determine if the program should quit

    // Main loop of the program
    do {
        // Display main menu options
        cout << "===========================================" << endl;
        cout << "Welcome to the Clinic Appointment System!" << endl;
        cout << "===========================================" << endl;
        cout << "1. Register/Create Account" << endl;
        cout << "2. Login" << endl;
        cout << "3. Quit Program" << endl;
        cout << "-------------------------------------------" << endl;

        int choice, entry = 0; // Variables to store user's choice and program's state
        string userType, fname, lname, userName, passcode; // Variables for user input
        validateInputType(choice); // Function to validate user input
        switch(choice) {
            case 1:
                // Account registration process
                cout << "Please select your account type [doctor/patient]: ";
                cin >> userType;
                while(userType != "doctor" && userType != "patient") {
                    cout << "Invalid input. Please enter doctor or patient: ";
                    cin >> userType;
                }
                if(userType == "doctor") {
                    int clinicToken;
                    cout << "Enter clinic token to certify that you are accredited: ";
                    cin >> clinicToken;
                    if(clinicToken == CLINIC_TOKEN) {
                        string fname, lname, password, email, specialization;
                        int startHour, endHour;
                        cout << "Enter your first name: ";
                        cin >> fname;
                        cout << "Enter your last name: ";
                        cin >> lname;
                        cout << "Enter your password: ";
                        cin >> password;
                        cout << "Enter your email: ";
                        cin >> email;
                        cout << "Enter your specialization: ";
                        cin >> specialization;
                        cout << "Enter your working hours(start hour end hour): ";
                        cin >> startHour >> endHour;
                        Doctor newDoctor(fname, lname, password, email, startHour, endHour, specialization);
                        doctorsByName[newDoctor.getUsername()] = newDoctor;
                        cout << "Doctor registration successful! Please login with credentials." << endl;
                    } else {
                        cout << "Fake doctor!!!\n";
                        cout << "Doctor registration blocked!!!\n";
                    }
                } else {
                    string fname, lname, password, email;
                    cout << "Enter your first name: ";
                    cin >> fname;
                    cout << "Enter your last name: ";
                    cin >> lname;
                    cout << "Enter your password: ";
                    cin >> password;
                    cout << "Enter your email: ";
                    cin >> email;
                    Patient newPatient(fname, lname, password, email);
                    patientsByName[newPatient.getUsername()] = newPatient;
                    cout << "Patient registration successful! Please login with credentials." << endl;
                }
                break;
            case 2:
                // Login process
                cout << "Please enter the category of your account before logging in[doctor/patient]: ";
                cin >> userType;
                // error checking
                while(userType != "doctor" && userType != "patient") {
                    cout << "Input must be doctor or patient. Enter valid input: ";
                    cin >> userType;
                }
                // asking for credentials
                cout << "Please enter your username(fname lname): ";
                cin >> fname >> lname;
                userName = fname + " " + lname;
                cout << "Please enter your password: ";
                cin >> passcode;
                if(userType == "doctor") {
                    do {
                        if(!isLoggedIn) {
                            isLoggedIn = login<Doctor>(userName, passcode, doctorsByName, entry);
                        }
                        if(isLoggedIn) {
                            int doctorChoice;
                            // Doctor menu options
                            cout << "-------------------------------------------" << endl;
                            cout << "Hello " << userName << "!\n";
                            cout << "-------------------------------------------" << endl;
                            cout << "1. View Appointments" << endl;
                            cout << "2. Cancel Appointment" << endl;
                            cout << "3. Logout" << endl;
                            cout << "-------------------------------------------" << endl;
                            validateInputType(doctorChoice);
                            vector<Appointment>* bookedAppointments;
                            switch(doctorChoice) {
                                case 1:
                                    bookedAppointments = doctorsByName[userName].getAppointments(appointments);
                                    doctorsByName[userName].viewAppointments(bookedAppointments);
                                    delete bookedAppointments;
                                    break;
                                case 2:
                                    doctorsByName[userName].cancelAppointment(appointments);
                                    break;
                                case 3:
                                    cout << "...Logging out...\n";
                                    isLoggedIn = false;
                                    entry = 3;
                                    break;
                                default:
                                    cout << "Invalid choice. Please try again." << endl;
                                    cout << "-------------------------------------------" << endl;
                                    break;
                            }
                        } else {
                            cout << "Kindly take action on login errors above!\n";
                            if(!(entry == 3)) {
                                char choice;
                                validateInputType<char>(choice);
                                switch(choice) {
                                    case 'y': {
                                        cout << "Enter password correctly: ";
                                        cin >> passcode;
                                        break;
                                    }
                                    case 'n': {
                                        entry = 3;
                                        break;
                                    }
                                    default: 
                                        cout << "Invalid selection, sending you to landing page.\n";
                                        entry = 3;
                                        break;
                                }
                            }
                        }
                    } while(entry != 3);
                } else {
                    // Patient login process
                    do {
                        if(!isLoggedIn) {
                            isLoggedIn = login<Patient>(userName, passcode, patientsByName, entry);
                        }
                        if(isLoggedIn) {
                            int patientChoice;
                            // Patient menu options
                            cout << "-------------------------------------------" << endl;
                            cout << "Hello " << userName << "!\n";
                            cout << "-------------------------------------------" << endl;
                            cout << "1. Book Appointment\n";
                            cout << "2. View Appointments\n";
                            cout << "3. Cancel Appointments\n";
                            cout << "4. Logout\n";
                            cout << "-------------------------------------------" << endl;
                            validateInputType(patientChoice);
                            vector<Appointment>* bookedAppointments;
                            switch(patientChoice) {
                                case 1:
                                    patientsByName[userName].bookAppointment(doctorsByName, appointments);
                                    break;
                                case 2:
                                    bookedAppointments = patientsByName[userName].getAppointments(appointments);
                                    patientsByName[userName].viewAppointments(bookedAppointments);
                                    delete bookedAppointments;
                                    break;
                                case 3:
                                    patientsByName[userName].cancelAppointment(appointments);
                                    break;
                                case 4:
                                    cout << "...Logging out...\n";
                                    isLoggedIn = false;
                                    entry = 4;
                                    break;
                                default:
                                    cout << "Invalid choice. Please try again." << endl;
                                    cout << "-------------------------------------------" << endl;
                                    break;
                            }
                        } else {
                            cout << "Kindly take action on login errors above!\n";
                            if(entry == 3) {
                                entry = 4;
                            } else {
                                char choice;
                                validateInputType<char>(choice);
                                switch(choice) {
                                    case 'y': {
                                        cout << "Enter password correctly: ";
                                        cin >> passcode;
                                        break;
                                    }
                                    case 'n': {
                                        entry = 4;
                                        break;
                                    }
                                    default: 
                                        cout << "Invalid selection, sending you to landing page.\n";
                                        entry = 4;
                                        break;
                                }
                            }
                        }
                    } while(entry != 4);
                }
                break;
            case 3:
                cout << "...Quitting the program...\n";
                quit = "y";
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while(quit == "n");

    return 0;
}