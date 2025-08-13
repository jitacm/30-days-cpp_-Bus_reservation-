#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "user.h"

using namespace std;

class Bus {
public:
    string bus_no;
    string driver;
    string arrival;
    string departure;
    string from;
    string to;
    string seats[8][4]; 
    Bus(string bno, string drv, string arr, string dep, string f, string t) {
        bus_no = bno;
        driver = drv;
        arrival = arr;
        departure = dep;
        from = f;
        to = t;

        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 4; j++)
                seats[i][j] = "Empty";
    }

    void showBusDetails() const { // Corrected: added const
        cout << "Bus No: " << bus_no << "\nDriver: " << driver << "\nFrom: " << from << "\nTo: " << to;
        cout << "\nArrival: " << arrival << "\nDeparture: " << departure << endl;
    }

    void showSeats() const { // Corrected: added const
        cout << "\nSeat Arrangement for Bus No " << bus_no << ":" << endl;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 4; j++) {
                int seat_no = i * 4 + j + 1;
                cout.width(4);
                cout << seat_no << ": ";
                cout.width(10);
                cout << seats[i][j] << "  ";
            }
            cout << endl;
        }
    }

    void reserveSeat() {
        int seat_no;
        cout << "Enter seat number (1-32): ";
        cin >> seat_no;
        if (cin.fail() || seat_no < 1 || seat_no > 32) {
            cout << "Invalid seat number!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
        int row = (seat_no - 1) / 4;
        int col = (seat_no - 1) % 4;
        if (seats[row][col] != "Empty") {
            cout << "Seat already booked!" << endl;
        } else {
            string name;
            cout << "Enter passenger name: ";
            cin >> name;
            seats[row][col] = name;
            cout << "Seat " << seat_no << " reserved for " << name << "." << endl;
        }
    }

    void cancelReservation() {
        int seat_no;
        cout << "Enter seat number to cancel (1-32): ";
        cin >> seat_no;
        if (cin.fail() || seat_no < 1 || seat_no > 32) {
            cout << "Invalid seat number!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
        int row = (seat_no - 1) / 4;
        int col = (seat_no - 1) % 4;
        if (seats[row][col] == "Empty") {
            cout << "Seat is already empty." << endl;
        } else {
            cout << "Reservation for " << seats[row][col] << " at seat " << seat_no << " canceled.\n";
            seats[row][col] = "Empty";
        }
    }

    void searchPassenger() {
        string name;
        cout << "Enter passenger name to search: ";
        cin >> name;
        bool found = false;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 4; j++) {
                if (seats[i][j] == name) {
                    int seat_no = i * 4 + j + 1;
                    cout << "Passenger " << name << " is in seat " << seat_no << " on bus " << bus_no << ".\n";
                    found = true;
                }
            }
        }
        if (!found)
            cout << "Passenger not found.\n";
    }

    void showSummary() const { // Corrected: added const
        int empty = 0, booked = 0;
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 4; j++)
                seats[i][j] == "Empty" ? empty++ : booked++;
        cout << "Total Booked: " << booked << ", Empty: " << empty << endl;
    }
};

vector<Bus> buses;

void installBus() {
    string bno, drv, arr, dep, from, to;
    cout << "Enter bus number: "; cin >> bno;
    cout << "Enter driver name: "; cin >> drv;
    cout << "Enter arrival time: "; cin >> arr;
    cout << "Enter departure time: "; cin >> dep;
    cout << "From: "; cin >> from;
    cout << "To: "; cin >> to;

    Bus b(bno, drv, arr, dep, from, to);
    buses.push_back(b);

    cout << "Bus Installed Successfully!\n";
}

void showAllBuses() {
    if (buses.empty()) {
        cout << "No buses available.\n";
        return;
    }
    for (size_t i = 0; i < buses.size(); ++i) {
        cout << "\nBus " << i + 1 << ":" << endl;
        buses[i].showBusDetails();
    }
}

void searchByRoute() {
    string from_location, to_location;
    cout << "\nEnter starting location: ";
    cin >> from_location;
    cout << "Enter destination: ";
    cin >> to_location;

    bool found = false;
    cout << "\n--- Available Buses on this Route ---\n";
    for (const auto& bus : buses) {
        if (bus.from == from_location && bus.to == to_location) {
            bus.showBusDetails();
            found = true;
        }
    }
    if (!found) {
        cout << "No buses found for this route.\n";
    }
}


int main() {
    string username, password;
    User::Role currentUserRole;
    int choice;
    bool exitProgram = false;

    do {
        cout << "\n===== Main Menu =====" << endl;
        cout << "1. Admin Login" << endl;
        cout << "2. Customer Access" << endl;
        cout << "3. Exit Program" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                cout << "Enter admin password: ";
                cin >> password;
                if (password == "5827") {
                    currentUserRole = User::ADMIN;
                    cout << "Admin login successful.\n";
                    int adminChoice;
                    do {
                        cout << "\n===== Admin Menu =====" << endl;
                        cout << "1. Install New Bus" << endl;
                        cout << "2. Search for Passenger" << endl;
                        cout << "3. Show Booking Summary" << endl;
                        cout << "4. Logout" << endl;
                        cout << "Enter choice: ";
                        cin >> adminChoice;

                        if (cin.fail()) {
                            cout << "Invalid input. Please enter a number.\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }

                        switch (adminChoice) {
                            case 1: installBus(); break;
                            case 2: 
                                if (buses.empty()) {
                                    cout << "No buses available.\n";
                                } else {
                                    // Assuming a bus needs to be selected for this operation
                                    buses[0].searchPassenger();
                                }
                                break;
                            case 3: 
                                if (buses.empty()) {
                                    cout << "No buses available.\n";
                                } else {
                                    // Assuming a bus needs to be selected for this operation
                                    buses[0].showSummary();
                                }
                                break;
                            case 4: cout << "Logging out...\n"; break;
                            default: cout << "Invalid choice!\n";
                        }
                    } while (adminChoice != 4);
                } else {
                    cout << "Incorrect password.\n";
                }
                break;

            case 2:
                currentUserRole = User::CUSTOMER;
                cout << "Customer access granted.\n";
                int customerChoice;
                do {
                    cout << "\n===== Customer Menu =====" << endl;
                    cout << "1. Show All Buses" << endl;
                    cout << "2. Reserve a Seat" << endl;
                    cout << "3. Cancel a Reservation" << endl;
                    cout << "4. Show Seat Arrangement" << endl;
                    cout << "5. Search Bus by Route" << endl;
                    cout << "6. Logout" << endl;
                    cout << "Enter choice: ";
                    cin >> customerChoice;

                    if (cin.fail()) {
                        cout << "Invalid input. Please enter a number.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }
                    
                    int index;
                    switch (customerChoice) {
                        case 1: showAllBuses(); break;
                        case 2:
                        case 3:
                        case 4:
                            if (buses.empty()) {
                                cout << "No buses available.\n";
                                break;
                            }
                            cout << "Enter bus index (1-" << buses.size() << "): ";
                            cin >> index;
                            if (cin.fail() || index < 1 || index > buses.size()) {
                                cout << "Invalid bus index.\n";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                break;
                            }
                            switch (customerChoice) {
                                case 2: buses[index - 1].reserveSeat(); break;
                                case 3: buses[index - 1].cancelReservation(); break;
                                case 4: buses[index - 1].showSeats(); break;
                            }
                            break;
                        case 5: searchByRoute(); break;
                        case 6: cout << "Logging out...\n"; break;
                        default: cout << "Invalid choice!\n";
                    }
                } while (customerChoice != 6);
                break;
            
            case 3:
                cout << "Exiting program...\n";
                exitProgram = true;
                break;

            default:
                cout << "Invalid choice!\n";
        }
    } while (!exitProgram);

    return 0;
}