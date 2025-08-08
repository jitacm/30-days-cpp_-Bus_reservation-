#include <iostream>
#include <vector>
#include <string>
#include <fstream>
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

    Bus() {} // Default constructor for loading from file

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
            cin.ignore();
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

vector<Bus> buses;

// Save buses to file
void saveData() {
    ofstream file("buses.txt");
    if (!file) return;

    file << buses.size() << "\n";
    for (auto &b : buses) {
        file << b.bus_no << "\n" << b.driver << "\n" << b.arrival << "\n"
             << b.departure << "\n" << b.from << "\n" << b.to << "\n";
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 4; j++)
                file << b.seats[i][j] << "\n";
    }
    file.close();
}

// Load buses from file
void loadData() {
    ifstream file("buses.txt");
    if (!file) return;

    size_t size;
    file >> size;
    file.ignore();
    buses.clear();

    for (size_t k = 0; k < size; k++) {
        Bus b;
        getline(file, b.bus_no);
        getline(file, b.driver);
        getline(file, b.arrival);
        getline(file, b.departure);
        getline(file, b.from);
        getline(file, b.to);

        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 4; j++)
                getline(file, b.seats[i][j]);

        buses.push_back(b);
    }
    file.close();
}

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
    saveData();
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
    loadData(); // Load existing data at start
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
                    if (index >= 1 && index <= buses.size()) {
                        buses[index-1].reserveSeat();
                        saveData();
                    }
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
                    if (index >= 1 && index <= buses.size()) {
                        buses[index-1].cancelSeat();
                        saveData();
                    }
                    else
                        cout << "Invalid bus index.\n";
                } else {
                    cout << "No buses to cancel reservation.\n";
                }
                break;
            case 5:
                searchBuses();
                break;
            case 6:
                saveData();
                cout << "Exiting...\n"; 
                break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}
