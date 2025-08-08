#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Minor edit to enable amend


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
// This function now supports multi-word input using getline()

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
            cin.ignore(); // flush newline before getline
            cout << "Enter passenger name: ";
            getline(cin, name);
            seats[row][col] = name;
            cout << "Seat " << seat_no << " reserved for " << name << "." << endl;
        }
    }

    void cancelSeat() {
        int seat_no;
        cout << "Enter seat number to cancel (1-32): ";
        cin >> seat_no;
        if (seat_no < 1 || seat_no > 32) {
            cout << "Invalid seat number!" << endl;
            return;
        }
        int row = (seat_no - 1) / 4;
        int col = (seat_no - 1) % 4;
        if (seats[row][col] == "Empty") {
            cout << "Seat is already empty!" << endl;
        } else {
            cout << "Reservation cancelled for Seat " << seat_no << "." << endl;
            seats[row][col] = "Empty";
        }
    }
};

// Global buses list
vector<Bus> buses;
// cin.ignore() used to flush newline before getline()


void installBus() {
    string bno, drv, arr, dep, from, to;
    cin.ignore(); // flush buffer before getline

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
        cout << "\nBus " << i+1 << ":" << endl;
        buses[i].showBusDetails();
    }
}

// Search buses by bus number, source, or destination
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
    switch (opt) {
        case 1:
            cout << "Enter bus number: ";
            cin >> query;
            for (size_t i = 0; i < buses.size(); ++i) {
                if (buses[i].bus_no == query) {
                    cout << "\nBus " << i+1 << ":\n";
                    buses[i].showBusDetails();
                    found = true;
                }
            }
            break;
        case 2:
            cout << "Enter source: ";
            cin >> query;
            for (size_t i = 0; i < buses.size(); ++i) {
                if (buses[i].from == query) {
                    cout << "\nBus " << i+1 << ":\n";
                    buses[i].showBusDetails();
                    found = true;
                }
            }
            break;
        case 3:
            cout << "Enter destination: ";
            cin >> query;
            for (size_t i = 0; i < buses.size(); ++i) {
                if (buses[i].to == query) {
                    cout << "\nBus " << i+1 << ":\n";
                    buses[i].showBusDetails();
                    found = true;
                }
            }
            break;
        default:
            cout << "Invalid search option!\n";
            return;
    }
    if (!found) {
        cout << "No matching buses found.\n";
    }
}

int main() {
    int choice;
    do {
        cout << "\n===== Bus Reservation System =====" << endl;
        cout << "1. Install New Bus" << endl;
        cout << "2. Show All Buses" << endl;
        cout << "3. Reserve a Seat" << endl;
        cout << "4. Cancel a Reservation" << endl;
        cout << "5. Search for Buses" << endl;
        cout << "6. Exit" << endl;
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
            case 4:
                if (!buses.empty()) {
                    int index;
                    cout << "Enter bus index (1-" << buses.size() << "): ";
                    cin >> index;
                    if (index >= 1 && index <= buses.size())
                        buses[index-1].cancelSeat();
                    else
                        cout << "Invalid bus index.\n";
                } else {
                    cout << "No buses to cancel reservation.\n";
                }
                break;
            case 5:
                searchBuses();
                break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}
