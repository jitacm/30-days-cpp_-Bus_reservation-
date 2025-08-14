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

    void listReservedSeats() {
        cout << "\nReserved Seats in Bus " << bus_no << ":\n";
        bool found = false;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (seats[i][j] != "Empty") {
                    int seat_num = i * 4 + j + 1;
                    cout << "Seat " << seat_num << ": " << seats[i][j] << endl;
                    found = true;
                }
            }
        }
        if (!found) cout << "No seats reserved.\n";
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

vector<Bus> buses;

void saveAllBuses() {
    ofstream out("buses.txt");
    out << buses.size() << '\n';
    for (auto &bus : buses)
        bus.saveToFile(out);
    out.close();
}

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

Bus* findBusByNumber(const string& number) {
    for (auto& bus : buses) {
        if (bus.bus_no == number)
            return &bus;
    }
    return nullptr;
}

void installBus() {
    string bno, drv, arr, dep, from, to;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\nEnter bus number: ";
    getline(cin, bno);
    if (findBusByNumber(bno)) {
        cout << "Bus with this number already exists!\n";
        return;
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
        cout << "5. Search Bus by Number" << endl;
        cout << "6. View Seat Arrangement" << endl;
        cout << "7. List Reserved Seats" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        string bus_no;
        Bus* bus;

        switch (choice) {
            case 1:
                installBus();
                break;
            case 2:
                if (buses.empty()) cout << "No buses available.\n";
                for (auto &b : buses) b.showBusDetails();
                break;
            case 3:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter bus number: "; getline(cin, bus_no);
                bus = findBusByNumber(bus_no);
                if (bus) { bus->reserveSeat(); saveAllBuses(); }
                else cout << "Bus not found!\n";
                break;
            case 4:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter bus number: "; getline(cin, bus_no);
                bus = findBusByNumber(bus_no);
                if (bus) { bus->cancelSeat(); saveAllBuses(); }
                else cout << "Bus not found!\n";
                break;
            case 5:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter bus number to search: "; getline(cin, bus_no);
                bus = findBusByNumber(bus_no);
                if (bus) bus->showBusDetails();
                else cout << "Bus not found!\n";
                break;
            case 6:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter bus number: "; getline(cin, bus_no);
                bus = findBusByNumber(bus_no);
                if (bus) bus->showSeats();
                else cout << "Bus not found!\n";
                break;
            case 7:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter bus number: "; getline(cin, bus_no);
                bus = findBusByNumber(bus_no);
                if (bus) bus->listReservedSeats();
                else cout << "Bus not found!\n";
                break;
            case 8:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 8);

    return 0;
}