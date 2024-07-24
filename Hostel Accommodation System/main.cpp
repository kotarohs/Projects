#include <iostream>
#include <sstream>
#include <fstream>
#include "db_connection.h"
#include <Python.h>

using namespace std;

void generate_qr_code(const string& data, const string& filename) {
    Py_Initialize();
    PyRun_SimpleString("import qrcode");
    string command = "img = qrcode.make('" + data + "')\nimg.save('" + filename + "')";
    PyRun_SimpleString(command.c_str());
    Py_Finalize();
}

void book_hostel() {
    int registration_id;
    string name;
    long long phone_number;

    cout << "Enter Registration ID: ";
    cin >> registration_id;
    cout << "Enter Name: ";
    cin >> name;
    cout << "Enter Phone Number: ";
    cin >> phone_number;

    try {
        sql::Connection* con = get_db_connection();
        sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO main (registration_id, name, phone_number) VALUES (?, ?, ?)");
        pstmt->setInt(1, registration_id);
        pstmt->setString(2, name);
        pstmt->setInt64(3, phone_number);
        pstmt->executeUpdate();
        delete pstmt;
        delete con;

        stringstream ss;
        ss << "Registration ID: " << registration_id << "\nName: " << name << "\nPhone: " << phone_number;
        generate_qr_code(ss.str(), "qr_code.png");

        cout << "Hostel booked successfully!" << endl;
    } catch (sql::SQLException &e) {
        cout << "Failed to book hostel: " << e.what() << endl;
    }
}

int main() {
    int choice;

    while (true) {
        cout << "Hostel Booking System" << endl;
        cout << "1. Book Hostel" << endl;
        cout << "2. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            book_hostel();
            break;
        case 2:
            exit(0);
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
