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
        cout << "Bus No: " << bus_no << "\nDriver: " << driver 
             << "\nFrom: " << from << "\nTo: " << to
             << "\nArrival: " << arrival << "\nDeparture: " << departure << endl;
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
            cin.ignore(); 
            cout << "Enter passenger name: ";
            getline(cin, name);
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
        cin.ignore();
        getline(cin, name);
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
    cin.ignore();
    cout << "Enter bus number: ";
    getline(cin, bno);
    cout << "Enter driver name: ";
    getline(cin, drv);
    cout << "Enter arrival time: ";
    getline(cin, arr);
    cout << "Enter departure time: ";
    getline(cin, dep);
    cout << "From: ";
    getline(cin, from);
    cout << "To: ";
    getline(cin, to);

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

void searchBuses() {
    if (buses.empty()) {
        cout << "No buses available to search.\n";
        return;
    }
    cout << "\nSearch by:\n";
    cout << "1. Bus Number\n2. Source\n3. Destination\nEnter option: ";
    int opt;
    cin >> opt;
    string query;
    bool found = false;
    cin.ignore();
    switch (opt) {
        case 1:
            cout << "Enter bus number: ";
            getline(cin, query);
            break;
        case 2:
            cout << "Enter source: ";
            getline(cin, query);
            break;
        case 3:
            cout << "Enter destination: ";
            getline(cin, query);
            break;
        default:
            cout << "Invalid search option!\n";
            return;
    }
    for (size_t i = 0; i < buses.size(); ++i) {
        if ((opt == 1 && buses[i].bus_no == query) ||
            (opt == 2 && buses[i].from == query) ||
            (opt == 3 && buses[i].to == query)) {
            cout << "\nBus " << i+1 << ":\n";
            buses[i].showBusDetails();
            found = true;
        }
    }
    if (!found) {
        cout << "No matching buses found.\n";
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
        cout << "8. Search for Buses" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice >= 3 && choice <= 7) {
            if (buses.empty()) {
                cout << "No buses available.\n";
                continue;
            }
            int index;
            cout << "Enter bus index (1-" << buses.size() << "): ";
            cin >> index;
            if (index < 1 || index > buses.size()) {
                cout << "Invalid bus index.\n";
                continue;
            }
            switch (choice) {
                case 3: buses[index - 1].reserveSeat(); break;
                case 4: buses[index - 1].cancelReservation(); break;
                case 5: buses[index - 1].searchPassenger(); break;
                case 6: buses[index - 1].showSeats(); break;
                case 7: buses[index - 1].showSummary(); break;
            }
        } 
        else if (choice == 1) installBus();
        else if (choice == 2) showAllBuses();
        else if (choice == 8) searchBuses();
        else if (choice == 9) cout << "Exiting...\n";
        else cout << "Invalid choice!\n";

    } while (choice != 9);

    return 0;
}
