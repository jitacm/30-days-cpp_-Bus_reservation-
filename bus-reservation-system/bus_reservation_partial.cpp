#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <iomanip>

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

    Bus() {}

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
        cout << "\nBus Number: " << bus_no << endl;
        cout << "Driver: " << driver << endl;
        cout << "From: " << from << "  To: " << to << endl;
        cout << "Arrival: " << arrival << "  Departure: " << departure << endl;
    }

    void showSeats() {
        cout << "\nSeat Arrangement for Bus No " << bus_no << ":" << endl;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 4; j++) {
                int seat_num = i * 4 + j + 1;
                cout.width(4);
                cout << "[" << seat_num << "]";
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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter passenger name: ";
            getline(cin, name);
            if (name.empty()) {
                cout << "Invalid name." << endl;
                return;
            }
            seats[row][col] = name;
            cout << "Seat " << seat_no << " reserved for " << name << "." << endl;
        }
    }

    void cancelSeat() {
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
            cout << "That seat is already empty." << endl;
        } else {
            cout << "Reservation for seat " << seat_no << " (" << seats[row][col] << ") cancelled." << endl;
            seats[row][col] = "Empty";
        }
    }

    void saveToFile(ofstream &out) {
        out << bus_no << '\n' << driver << '\n' << arrival << '\n' << departure << '\n' << from << '\n' << to << '\n';
        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < 4; ++j)
                out << seats[i][j] << '\n';
    }

    void loadFromFile(ifstream &in) {
        getline(in, bus_no);
        getline(in, driver);
        getline(in, arrival);
        getline(in, departure);
        getline(in, from);
        getline(in, to);
        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < 4; ++j)
                getline(in, seats[i][j]);
    }
};

// Global bus storage
vector<Bus> buses;

// Save all buses to file
void saveAllBuses() {
    ofstream out("buses.txt");
    out << buses.size() << '\n';
    for (auto &bus : buses)
        bus.saveToFile(out);
    out.close();
}

// Load all buses from file
void loadAllBuses() {
    ifstream in("buses.txt");
    if (!in) return;
    int n;
    in >> n;
    in.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int i = 0; i < n; ++i) {
        Bus b;
        b.loadFromFile(in);
        buses.push_back(b);
    }
    in.close();
}

// Show all buses
void showAllBuses() {
    if (buses.empty()) {
        cout << "No buses available.\n";
        return;
    }
    for (size_t i = 0; i < buses.size(); i++) {
        cout << "\nBus " << (i+1) << ":";
        buses[i].showBusDetails();
        buses[i].showSeats();
    }
}

// Search for buses by number or route
void searchBuses() {
    if (buses.empty()) {
        cout << "No buses available.\n";
        return;
    }
    string query;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter bus number or route to search: ";
    getline(cin, query);

    bool found = false;
    for (auto &bus : buses) {
        if (bus.bus_no == query || bus.from == query || bus.to == query) {
            bus.showBusDetails();
            bus.showSeats();
            found = true;
        }
    }
    if (!found) {
        cout << "No matching buses found.\n";
    }
}

// Export passenger list to file
void exportPassengerList(int busIndex) {
    if (busIndex < 0 || busIndex >= (int)buses.size()) {
        cout << "Invalid bus index.\n";
        return;
    }

    const Bus& b = buses[busIndex];
    string filename = "passenger_list_" + b.bus_no + ".txt";

    ofstream out(filename);
    if (!out.is_open()) {
        cout << "Failed to create file: " << filename << "\n";
        return;
    }

    out << "Passenger List for Bus " << b.bus_no << "\n";
    out << "Driver: " << b.driver << "\n";
    out << "Route: " << b.from << " -> " << b.to << "\n";
    out << "Arrival: " << b.arrival << " | Departure: " << b.departure << "\n";
    out << "---------------------------------------------\n";

    int seatNumber = 1;
    int reservedCount = 0, emptyCount = 0;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 4; ++j) {
            const string& name = b.seats[i][j];
            out << "Seat " << seatNumber << ": " << name << "\n";
            if (name != "Empty") reservedCount++;
            else emptyCount++;
            seatNumber++;
        }
    }

    out << "---------------------------------------------\n";
    out << "Total Seats: 32\n";
    out << "Reserved: " << reservedCount << "\n";
    out << "Empty: " << emptyCount << "\n";

    out.close();
    cout << "✅ Exported passenger list to: " << filename << "\n";
}

// Install a new bus
void installBus() {
    string bno, drv, arr, dep, from, to;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\nEnter bus number: ";
    getline(cin, bno);

    for (auto &bus : buses) {
        if (bus.bus_no == bno) {
            cout << "Bus with this number already exists!\n";
            return;
        }
    }

    cout << "Enter driver name: "; getline(cin, drv);
    cout << "Enter arrival time: "; getline(cin, arr);
    cout << "Enter departure time: "; getline(cin, dep);
    cout << "From: "; getline(cin, from);
    cout << "To: "; getline(cin, to);

    Bus b(bno, drv, arr, dep, from, to);
    buses.push_back(b);
    cout << "Bus Installed Successfully!\n";
    saveAllBuses();
}

int main() {
    loadAllBuses();
    int choice;
    do {
        cout << "\n===== Bus Reservation System =====" << endl;
        cout << "1. Install New Bus" << endl;
        cout << "2. Show All Buses" << endl;
        cout << "3. Reserve a Seat" << endl;
        cout << "4. Cancel a Reservation" << endl;
        cout << "5. Search for Buses" << endl;
        cout << "6. Export Passenger List to File" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter choice: ";

        cin >> choice;

        if (cin.fail()) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: installBus(); break;
            case 2: showAllBuses(); break;
            case 3:
                if (!buses.empty()) {
                    int index;
                    cout << "Enter bus index (1-" << buses.size() << "): ";
                    cin >> index;
                    if (index >= 1 && index <= (int)buses.size())
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
                    if (index >= 1 && index <= (int)buses.size())
                        buses[index-1].cancelSeat();
                    else
                        cout << "Invalid bus index.\n";
                } else {
                    cout << "No buses to cancel reservation.\n";
                }
                break;
            case 5: searchBuses(); break;
            case 6:
                if (buses.empty()) {
                    cout << "No buses available to export.\n";
                    break;
                }
                {
                    int index;
                    cout << "Enter bus index (1-" << buses.size() << "): ";
                    cin >> index;
                    if (index >= 1 && index <= (int)buses.size())
                        exportPassengerList(index - 1);
                    else
                        cout << "Invalid bus index.\n";
                }
                break;
            case 7: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 7);

    return 0;
}
