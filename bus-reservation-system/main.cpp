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

    void showBusDetails() {
        cout << "Bus No: " << bus_no << "\nDriver: " << driver << "\nFrom: " << from << "\nTo: " << to;
        cout << "\nArrival: " << arrival << "\nDeparture: " << departure << endl;
    }

    void showSeats() {
        cout << "\nSeat Arrangement for Bus No " << bus_no << ":\n";
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
        if (seat_no < 1 || seat_no > 32) {
            cout << "❌ Invalid seat number!" << endl;
            return;
        }
        int row = (seat_no - 1) / 4;
        int col = (seat_no - 1) % 4;
        if (seats[row][col] != "Empty") {
            cout << "❌ Seat already booked!" << endl;
        } else {
            string name;
            cout << "Enter passenger name: ";
            cin >> name;
            seats[row][col] = name;
            cout << "✅ Seat " << seat_no << " reserved for " << name << "." << endl;
        }
    }

    void cancelReservation() {
        int seat_no;
        cout << "Enter seat number to cancel (1–32): ";
        cin >> seat_no;
        if (seat_no < 1 || seat_no > 32) {
            cout << "❌ Invalid seat number!" << endl;
            return;
        }
        int row = (seat_no - 1) / 4;
        int col = (seat_no - 1) % 4;
        if (seats[row][col] == "Empty") {
            cout << "❌ Seat is already empty." << endl;
        } else {
            cout << "✔️ Reservation for " << seats[row][col] << " at seat " << seat_no << " canceled.\n";
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
                    cout << "✅ Passenger " << name << " is in seat " << seat_no << " on bus " << bus_no << ".\n";
                    found = true;
                }
            }
        }
        if (!found)
            cout << "❌ Passenger not found.\n";
    }

    void showSummary() {
        int empty = 0, booked = 0;
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 4; j++)
                seats[i][j] == "Empty" ? empty++ : booked++;
        cout << "📊 Total Booked: " << booked << ", Empty: " << empty << endl;
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

    cout << "✅ Bus Installed Successfully!\n";
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


int main() {
    int choice;
    do {
        cout << "\n===== 🚍 Bus Reservation System =====" << endl;
        cout << "1. Install New Bus" << endl;
        cout << "2. Show All Buses" << endl;
        cout << "3. Reserve a Seat" << endl;
        cout << "4. Cancel a Reservation" << endl;
        cout << "5. Search for Passenger" << endl;
        cout << "6. Show Seat Arrangement" << endl;
        cout << "7. Show Booking Summary" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: installBus(); break;
        case 2: showAllBuses(); break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            if (buses.empty()) {
                cout << "No buses available.\n";
                break;
            }
            int index;
            cout << "Enter bus index (1-" << buses.size() << "): ";
            cin >> index;
            if (index < 1 || index > buses.size()) {
                cout << "Invalid bus index.\n";
                break;
            }
            switch (choice) {
            case 3: buses[index - 1].reserveSeat(); break;
            case 4: buses[index - 1].cancelReservation(); break;
            case 5: buses[index - 1].searchPassenger(); break;
            case 6: buses[index - 1].showSeats(); break;
            case 7: buses[index - 1].showSummary(); break;
            }
            break;
        case 8: cout << "Exiting...\n"; break;
        default: cout << "Invalid choice!\n";
        }

    } while (choice != 8);

    return 0;
}
