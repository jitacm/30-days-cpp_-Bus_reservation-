#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

// ---- Forward declarations (needed because Bus methods call these) ----
void saveToFile();
void loadFromFile();

// ---- Helper: check file existence (works everywhere, no <filesystem>) ----
bool fileExists(const string& filename) {
    ifstream f(filename);
    return f.good();
}

// ---- Helper: split a string by a delimiter ----
vector<string> split(const string& s, char delim) {
    vector<string> out;
    string item;
    stringstream ss(s);
    while (getline(ss, item, delim)) out.push_back(item);
    return out;
}

// =========================== Bus class ===========================
class Bus {
public:
    string bus_no;
    string driver;
    string arrival;
    string departure;
    string from;
    string to;
    string seats[8][4];         // 32 seats
    double fare_per_seat;       // NEW
    string status;              // NEW

    Bus(string bno, string drv, string arr, string dep, string f, string t)
        : bus_no(bno), driver(drv), arrival(arr), departure(dep), from(f), to(t),
          fare_per_seat(0.0), status("On Time") {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 4; j++)
                seats[i][j] = "Empty";
    }

    void showBusDetails() {
        cout << "Bus No: " << bus_no
             << "\nDriver: " << driver
             << "\nFrom: " << from
             << "\nTo: " << to
             << "\nArrival: " << arrival
             << "\nDeparture: " << departure
             << "\nFare per Seat: " << fare_per_seat
             << "\nStatus: " << status << endl;
    }

    void showSeats() {
        cout << "\nSeat Arrangement for Bus No " << bus_no << ":\n";
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
            cout << "Invalid seat number!\n";
            return;
        }
        int row = (seat_no - 1) / 4;
        int col = (seat_no - 1) % 4;
        if (seats[row][col] != "Empty") {
            cout << "Seat already booked!\n";
        } else {
            string name;
            cin.ignore();
            cout << "Enter passenger name: ";
            getline(cin, name);
            seats[row][col] = name;
            cout << "Seat " << seat_no << " reserved for " << name
                 << ". Fare: " << fare_per_seat << "\n";
            saveToFile();
        }
    }

    void cancelSeat() {
        int seat_no;
        cout << "Enter seat number to cancel (1-32): ";
        cin >> seat_no;
        if (seat_no < 1 || seat_no > 32) {
            cout << "Invalid seat number!\n";
            return;
        }
        int row = (seat_no - 1) / 4;
        int col = (seat_no - 1) % 4;
        if (seats[row][col] == "Empty") {
            cout << "Seat is already empty!\n";
        } else {
            cout << "Reservation cancelled for Seat " << seat_no << ".\n";
            seats[row][col] = "Empty";
            saveToFile();
        }
    }
};

// =========================== Globals ===========================
vector<Bus> buses;

// =========================== Core Actions ===========================
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
    saveToFile();

    cout << "✅ Bus Installed Successfully!\n";
}

void showAllBuses() {
    if (buses.empty()) {
        cout << "No buses available.\n";
        return;
    }
    for (size_t i = 0; i < buses.size(); ++i) {
        cout << "\nBus " << i + 1 << ":\n";
        buses[i].showBusDetails();
        buses[i].showSeats();
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
            for (size_t i = 0; i < buses.size(); ++i)
                if (buses[i].bus_no == query) { cout << "\nBus " << i+1 << ":\n"; buses[i].showBusDetails(); found = true; }
            break;
        case 2:
            cout << "Enter source: ";
            cin >> query;
            for (size_t i = 0; i < buses.size(); ++i)
                if (buses[i].from == query) { cout << "\nBus " << i+1 << ":\n"; buses[i].showBusDetails(); found = true; }
            break;
        case 3:
            cout << "Enter destination: ";
            cin >> query;
            for (size_t i = 0; i < buses.size(); ++i)
                if (buses[i].to == query) { cout << "\nBus " << i+1 << ":\n"; buses[i].showBusDetails(); found = true; }
            break;
        default:
            cout << "Invalid search option!\n";
            return;
    }
    if (!found) cout << "No matching buses found.\n";
}

// =========================== Admin Features (Level-3) ===========================
bool adminLogin() {
    string pass;
    cout << "Enter admin password: ";
    cin >> pass;
    return pass == "admin123";
}

void setBusFare() {
    if (!adminLogin()) { cout << "❌ Wrong password!\n"; return; }
    if (buses.empty()) { cout << "No buses available.\n"; return; }

    int index;
    cout << "Enter bus index (1-" << buses.size() << "): ";
    cin >> index;
    if (index < 1 || (size_t)index > buses.size()) { cout << "Invalid bus index.\n"; return; }

    double fare;
    cout << "Enter fare per seat: ";
    cin >> fare;
    buses[index - 1].fare_per_seat = fare;
    cout << "✅ Fare updated!\n";
    saveToFile();
}

void setBusStatus() {
    if (!adminLogin()) { cout << "❌ Wrong password!\n"; return; }
    if (buses.empty()) { cout << "No buses available.\n"; return; }

    int index;
    cout << "Enter bus index (1-" << buses.size() << "): ";
    cin >> index;
    if (index < 1 || (size_t)index > buses.size()) { cout << "Invalid bus index.\n"; return; }

    cout << "Enter status (On Time / Delayed / Cancelled): ";
    string newStatus;
    cin.ignore();
    getline(cin, newStatus);
    buses[index - 1].status = newStatus;
    cout << "✅ Status updated!\n";
    saveToFile();
}

// =========================== Persistence ===========================
// Format per bus in buses.txt:
// Header line with 8 fields separated by '|':
// bus_no|driver|arrival|departure|from|to|fare_per_seat|status
// Followed by 32 lines: each seat value (one per line)
void saveToFile() {
    ofstream fout("buses.txt");
    if (!fout.is_open()) {
        cout << "❌ Could not open buses.txt for writing.\n";
        return;
    }
    for (const auto& bus : buses) {
        fout << bus.bus_no << "|" << bus.driver << "|" << bus.arrival << "|"
             << bus.departure << "|" << bus.from << "|" << bus.to << "|"
             << bus.fare_per_seat << "|" << bus.status << "\n";
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 4; j++)
                fout << bus.seats[i][j] << "\n";
    }
    fout.close();
}

void loadFromFile() {
    if (!fileExists("buses.txt")) return;

    ifstream fin("buses.txt");
    if (!fin.is_open()) return;

    buses.clear();

    string header;
    while (getline(fin, header)) {
        if (header.empty()) continue;
        auto parts = split(header, '|');

        // Backward compatibility: old files had 6 parts (no fare/status)
        if (parts.size() < 6) break;

        string bno   = parts[0];
        string drv   = parts[1];
        string arr   = parts[2];
        string dep   = parts[3];
        string from  = parts[4];
        string to    = parts[5];

        Bus b(bno, drv, arr, dep, from, to);

        if (parts.size() >= 7) {
            try { b.fare_per_seat = stod(parts[6]); }
            catch(...) { b.fare_per_seat = 0.0; }
        }
        if (parts.size() >= 8) b.status = parts[7];

        // Read 32 seat lines (if file ends early, fill "Empty")
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 4; j++) {
                string seatLine;
                if (!getline(fin, seatLine)) seatLine = "Empty";
                b.seats[i][j] = seatLine.empty() ? "Empty" : seatLine;
            }
        }
        buses.push_back(b);
    }
    fin.close();
}

// =========================== Main ===========================
int main() {
    loadFromFile(); // Load data when app starts
    int choice;
    do {
        cout << "\n===== Bus Reservation System =====\n";
        cout << "1. Install New Bus\n";
        cout << "2. Show All Buses\n";
        cout << "3. Reserve a Seat\n";
        cout << "4. Cancel a Reservation\n";
        cout << "5. Search for Buses\n";
        cout << "6. Exit\n";
        cout << "7. Set Bus Fare (Admin)\n";
        cout << "8. Set Bus Status (Admin)\n";
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
                    if (index >= 1 && (size_t)index <= buses.size())
                        buses[index-1].reserveSeat();
                    else
                        cout << "Invalid bus index.\n";
                } else cout << "No buses to reserve.\n";
                break;
            case 4:
                if (!buses.empty()) {
                    int index;
                    cout << "Enter bus index (1-" << buses.size() << "): ";
                    cin >> index;
                    if (index >= 1 && (size_t)index <= buses.size())
                        buses[index-1].cancelSeat();
                    else
                        cout << "Invalid bus index.\n";
                } else cout << "No buses to cancel reservation.\n";
                break;
            case 5: searchBuses(); break;
            case 7: setBusFare(); break;
            case 8: setBusStatus(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 6);
    return 0;
}
