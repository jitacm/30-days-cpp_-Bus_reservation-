#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

struct Booking {
    string bookingID;
    string passengerName;
    int seatNo;
};

class Bus {
public:
    string bus_no, driver, arrival, departure, from, to;
    string seats[8][4]; // 32 seats
    vector<Booking> bookings;

    static int bookingCounter; // shared counter for all bookings

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
        cout << "Bus No: " << bus_no
             << "\nDriver: " << driver
             << "\nFrom: " << from
             << "\nTo: " << to
             << "\nArrival: " << arrival
             << "\nDeparture: " << departure << "\n";
    }

    // Feature 6 - Seat map with X for booked
    void showSeatMap() {
        cout << "\nSeat Map for Bus " << bus_no << ":\n";
        int seatNo = 1;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 4; j++) {
                if (seats[i][j] == "Empty")
                    cout << setw(5) << seatNo;
                else
                    cout << setw(5) << "X";
                seatNo++;
            }
            cout << "\n";
        }
    }

    // Feature 9 - Generate Booking ID
    string generateBookingID() {
        bookingCounter++;
        return "TCKT" + string(4 - to_string(bookingCounter).length(), '0') + to_string(bookingCounter);
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
            cout << "Enter passenger name: ";
            cin >> name;
            seats[row][col] = name;

            string bookingID = generateBookingID();
            bookings.push_back({bookingID, name, seat_no});

            cout << "✅ Seat " << seat_no << " reserved for " << name
                 << ". Booking ID: " << bookingID << "\n";
        }
    }

    // Feature 10 - Cancel using Booking ID
    void cancelByBookingID() {
        string id;
        cout << "Enter booking ID to cancel: ";
        cin >> id;
        bool found = false;

        for (size_t i = 0; i < bookings.size(); i++) {
            if (bookings[i].bookingID == id) {
                int seat_no = bookings[i].seatNo;
                int row = (seat_no - 1) / 4;
                int col = (seat_no - 1) % 4;

                seats[row][col] = "Empty";
                cout << "❌ Reservation cancelled for Seat " << seat_no
                     << " (" << bookings[i].passengerName << ").\n";

                bookings.erase(bookings.begin() + i);
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Booking ID not found!\n";
        }
    }
};

int Bus::bookingCounter = 0; // initialize static variable

vector<Bus> buses;

void installBus() {
    string bno, drv, arr, dep, from, to;
    cout << "Enter bus number: "; cin >> bno;
    cout << "Enter driver name: "; cin >> drv;
    cout << "Enter arrival time: "; cin >> arr;
    cout << "Enter departure time: "; cin >> dep;
    cout << "From: "; cin >> from;
    cout << "To: "; cin >> to;

    buses.push_back(Bus(bno, drv, arr, dep, from, to));
    cout << "✅ Bus Installed Successfully!\n";
}

void showAllBuses() {
    if (buses.empty()) {
        cout << "No buses available.\n";
        return;
    }
    for (size_t i = 0; i < buses.size(); i++) {
        cout << "\nBus " << i + 1 << ":\n";
        buses[i].showBusDetails();
    }
}

int main() {
    int choice;
    while (true) {
        cout << "\n===== Bus Reservation Menu =====\n";
        cout << "1. Install Bus\n";
        cout << "2. Show All Buses\n";
        cout << "3. Reserve Seat\n";
        cout << "4. Cancel Ticket (Booking ID)\n";
        cout << "5. Show Seat Map\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) installBus();
        else if (choice == 2) showAllBuses();
        else if (choice == 3) {
            if (buses.empty()) cout << "No buses available.\n";
            else {
                int busIndex;
                cout << "Enter bus number (1-" << buses.size() << "): ";
                cin >> busIndex;
                if (busIndex >= 1 && busIndex <= buses.size())
                    buses[busIndex - 1].reserveSeat();
                else
                    cout << "Invalid bus selection!\n";
            }
        }
        else if (choice == 4) {
            if (buses.empty()) cout << "No buses available.\n";
            else {
                int busIndex;
                cout << "Enter bus number (1-" << buses.size() << "): ";
                cin >> busIndex;
                if (busIndex >= 1 && busIndex <= buses.size())
                    buses[busIndex - 1].cancelByBookingID();
                else
                    cout << "Invalid bus selection!\n";
            }
        }
        else if (choice == 5) {
            if (buses.empty()) cout << "No buses available.\n";
            else {
                int busIndex;
                cout << "Enter bus number (1-" << buses.size() << "): ";
                cin >> busIndex;
                if (busIndex >= 1 && busIndex <= buses.size())
                    buses[busIndex - 1].showSeatMap();
                else
                    cout << "Invalid bus selection!\n";
            }
        }
        else if (choice == 6) {
            cout << "Exiting... Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid choice! Try again.\n";
        }
    }
    return 0;
}
