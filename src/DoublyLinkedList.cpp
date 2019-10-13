
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "DoublyLinkedList.h"
//#include <vector>
using namespace std;



DoublyLinkedList::DoublyLinkedList() {
    this->head = nullptr;
    this->location = nullptr;
}
DoublyLinkedList::~DoublyLinkedList() { // DO
    // remove all
}

// INSERT:
void DoublyLinkedList::initializeList(string fName, string lName, string phone, string apts) {
    Patient *newPatient = new Patient;
    newPatient->fName = fName;
    newPatient->lName = lName;
    newPatient->phoneNumber = phone;
    
    // ADD APPOINTMENT INFORMATION IN LATER, for now ignore... ********************************************
    
    // insert node (list should be in alphabetical order from the start)
    location = head;
    if (location == nullptr) { // insert first and only node
        head = newPatient;
        newPatient->next = nullptr;
        newPatient->prev = nullptr;
        tail = newPatient; // set tail
    } else { // insert after tail.
        tail->next = newPatient;
        newPatient->prev = tail;
        newPatient->next = nullptr;
        tail = newPatient;
    }
}
void DoublyLinkedList::appendPatient() { // Assumes all names start w/ capital letters (fix)
    // Prepare new patient 'node'
    cout << "ADD A NEW PATIENT: " << endl;
    Patient *newPatient = new Patient;
    cout << "First Name: ";
    cin >> newPatient->fName;
    cout << "Last Name: ";
    cin >> newPatient->lName;
    cout << "Phone Number: ";
    cin >> newPatient->phoneNumber;

    Appointment *newAppointment = new Appointment;
    cout << "Appointment Date: ";
    cin >> newAppointment->date;
    cout << "Appointment Time: ";
    cin >> newAppointment->time;
    
    newPatient->appointments.push_back(*newAppointment);
    
    // Find location to insert after:
    location = head;
    prevLoc = nullptr;
    while ((location != nullptr) && (newPatient->lName > location->lName)) { // next location
//        cout << newPatient->lName << " > " << location->lName << endl;
        prevLoc = location;
        location = location->next;
    }

    // Insert 'node' between prevLoc and location
    if (prevLoc == nullptr && location == nullptr) { // make only first 'node'
//        cout << "1" << endl;
        head = newPatient;
        newPatient->next = nullptr;
        newPatient->prev = nullptr;
    } else if (location == nullptr) { // if at end
//        cout << "3" << endl;
        prevLoc->next = newPatient;
        newPatient->prev = prevLoc;
        newPatient->next = nullptr;
        tail = newPatient; // set tail
    } else if (prevLoc == nullptr) { // insert first node before location
//        cout << "2" << endl;
        head = newPatient;
        newPatient->next = location;
        location->prev = newPatient;
        newPatient->prev = nullptr;
    } else { // in the middle and before location
//        cout << "4" << endl;
        prevLoc->next = newPatient;
        location->prev = newPatient;
        newPatient->prev = prevLoc;
        newPatient->next = location;
    }
    
//    cout << "END" <<endl;
}

DoublyLinkedList::Patient* DoublyLinkedList::findPatient() {
    Patient* tempPatient = new Patient;
    bool foundPatient = false;
    
    string lName, fName;
    cout << "Last Name of Patient to Edit: ";
    cin >> lName;
    cout << "First Name of Patient to Edit: ";
    cin >> fName;
    
    // serches and returns 'node'
    location = head;
    if (location != nullptr) {
        while (location != nullptr) {
            if (location->lName == lName && location->fName == fName) {
                tempPatient = location;
                foundPatient = true;
            }
            location = location->next;
        }
    }
    if (!foundPatient) { // if not found set pointer to nullptr
        tempPatient = nullptr;
    }
    return tempPatient;
}

// EDIT:
void DoublyLinkedList::editAppointmentForPatient() {
    Patient* tempPatient = findPatient();
    
    if (tempPatient == nullptr) {
        cout << "The Patient was not found." << endl;
    } else {
        cout << "Patient: " << tempPatient->fName << " " << tempPatient->lName << endl;
    }
    
    Appointment *newAppointment = new Appointment;
    cout << "Add Apt Date: ";
    cin >> newAppointment->date;
    cout << "Add Apt Time: ";
    cin >> newAppointment->time;
    
    tempPatient->appointments.push_back(*newAppointment); // DOES NOT WORK AS EXPECTED
    
    for (int i = 0; i < tempPatient->appointments.size(); i++) { // this works though
        cout << "\t\t" << tempPatient->appointments[i].date << " at " << tempPatient
        ->appointments[i].time << endl;
    }
    
    delete tempPatient; // seems to delete all appointment information for patient node like it should not do.
}

// REMOVE:
void DoublyLinkedList::removePatient() {
    
}

// VIEW:
void DoublyLinkedList::viewPatients() {
    cout << "\n--- All Patients and Appointments ---\n" << endl;
    location = head;
    if (head == nullptr) {
        cout << "List is empty" << endl;
    } else {
        while (location != nullptr) {
            cout << location->lName << ", " << location->fName << endl;
            cout << "\tPhone: " << location->phoneNumber << endl;;
            cout << "\tAppointments and times: " << endl;
            for (int i = 0; i < location->appointments.size(); i++) {
                cout << "\t\t" << location->appointments[i].date << " at " << location->appointments[i].time << endl;
            }
            location = location->next;
        }
    }
    cout << "-----------------------------------------\n" << endl;
}

// SORTS:
//    void alphabeticSort(); // sorts list in alphabetical order
//    void dateSort(); // sort in order of upcoming appointments

// TEXT:
void DoublyLinkedList::textSender() { // calls texting function
    
}
// File Reader:
void DoublyLinkedList::fileReader() {
    string line;
    ifstream readFile("Patients.txt");
    if (readFile.is_open()) {
        while(getline(readFile,line)) {
            cout << line << endl; // break up each line into inputs for initialize
            //initializeList("Bob", "Smith", "8937238294", "long string of apt information to be included later");
        }
        readFile.close();
    } else {
        cout << "Could not read from file."; 
    }
}
// File Writer:
void DoublyLinkedList::fileWriter() {
    
    // Prepare & write one string per patient
    location = head;
    if (head == nullptr) {
        cout << "List is empty, nothing to write" << endl;
    } else {
        while (location != nullptr) {
            string appendLine;
            appendLine = location->lName + "\t\t\t" + location->fName + "\t\t\t" + location->phoneNumber; // needs better formatting than tabs probably
            // figure out how to implement and add location->appointments

            // String of appointments:
            for (int i = 0; i < location->appointments.size(); i++) {
                appendLine = appendLine + location->appointments[i].date + " at " + location->appointments[i].time + " ";
            }
            appendLine = appendLine + "\n";
            
            cout << "APPENDING: " << appendLine; // idea of what will be appended
            // APPEND LINE TO TEXT DOC HERE ----------------------------------------------------------------
            
            location = location->next;
        }
    }
    
}
