#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Bus {
public:
    string bus_no;
    string driver;
    string arrival;
    string departure;
    string from;
    string to;
    string seats[8][4]; // 32 seats

    Bus(string bno, string drv, string arr, string dep, string f, string t) {
        bus_no = bno;
        driver = drv;
        arrival = arr;
        departure = dep;
        from = f;
        to = t;

        // initialize seats
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 4; j++)
                seats[i][j] = "Empty";
    }

    void showBusDetails() {
        cout << "Bus No: " << bus_no << "\nDriver: " << driver << "\nFrom: " << from << "\nTo: " << to;
        cout << "\nArrival: " << arrival << "\nDeparture: " << departure << endl;
    }

    void showSeats() {
        cout << "\nSeat Arrangement for Bus No " << bus_no << ":" << endl;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 4; j++) {
                cout.width(12);
                cout << seats[i][j];
            }
            cout << endl;
        }
    }

    void reserveSeat() {
        int seat_no;
        cout << "Enter seat number (1-32): ";
        cin >> seat_no;
        if (seat_no < 1 || seat_no > 32) {
            cout << "Invalid seat number!" << endl;
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
};

// Global buses list
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

    cout << "✅ Bus Installed Successfully!\n";
}

void showAllBuses() {
    if (buses.empty()) {
        cout << "No buses available.\n";
        return;
    }

    for (size_t i = 0; i < buses.size(); ++i) {
        cout << "\nBus " << i+1 << ":" << endl;
        buses[i].showBusDetails();
    }
}

// Main menu (reservation search/cancel not yet implemented)
int main() {
    int choice;
    do {
        cout << "\n===== Bus Reservation System (Partial) =====" << endl;
        cout << "1. Install New Bus" << endl;
        cout << "2. Show All Buses" << endl;
        cout << "3. Reserve a Seat" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: installBus(); break;
            case 2: showAllBuses(); break;
            case 3:
                if (!buses.empty()) {
                    int index;
                    cout << "Enter bus index (1-" << buses.size() << "): ";
                    cin >> index;
                    if (index >= 1 && index <= buses.size())
                        buses[index-1].reserveSeat();
                    else
                        cout << "Invalid bus index.\n";
                } else {
                    cout << "No buses to reserve.\n";
                }
                break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 4);

    return 0;
}