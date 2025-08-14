#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip> // Add this header for I/O manipulators
#include "user.h"

// Define constants for magic numbers
const int TOTAL_ROWS = 8;
const int SEATS_PER_ROW = 4;
const int TOTAL_SEATS = TOTAL_ROWS * SEATS_PER_ROW;

// A helper function to get a string from user input
std::string getLineFromUser(const std::string& prompt) {
    std::string input_buffer;
    std::cout << prompt;
    std::getline(std::cin, input_buffer);
    return input_buffer;
}

// A helper function to get an integer from user input with validation
int getIntFromUser(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value < min || value > max) {
            std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            // Clear the input buffer after a successful integer read
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

class Bus {
public:
    std::string bus_no;
    std::string driver;
    std::string arrival;
    std::string departure;
    std::string from;
    std::string to;
    std::string seats[TOTAL_ROWS][SEATS_PER_ROW];

    // Default constructor
    Bus() {
        initializeSeats();
    }

    // Parameterized constructor
    Bus(const std::string& bno, const std::string& drv, const std::string& arr, const std::string& dep, const std::string& f, const std::string& t) {
        this->bus_no = bno;
        this->driver = drv;
        this->arrival = arr;
        this->departure = dep;
        this->from = f;
        this->to = t;
        initializeSeats();
    }
    
    // Explicit seat initialization function
    void initializeSeats() {
        for (int i = 0; i < TOTAL_ROWS; ++i) {
            for (int j = 0; j < SEATS_PER_ROW; ++j) {
                this->seats[i][j] = "Empty";
            }
        }
    }

    void showBusDetails() const {
        std::cout << "--------------------------------\n";
        std::cout << "Bus No: " << this->bus_no << "\n";
        std::cout << "Driver: " << this->driver << "\n";
        std::cout << "From: " << this->from << "\n";
        std::cout << "To: " << this->to << "\n";
        std::cout << "Arrival Time: " << this->arrival << "\n";
        std::cout << "Departure Time: " << this->departure << "\n";
        std::cout << "--------------------------------\n";
    }

    void showSeats() const {
        std::cout << "\n===== Seat Arrangement for Bus " << this->bus_no << " =====\n";
        for (int i = 0; i < TOTAL_ROWS; ++i) {
            for (int j = 0; j < SEATS_PER_ROW; ++j) {
                int seat_number = (i * SEATS_PER_ROW) + j + 1;
                std::cout << std::setw(3) << std::left << seat_number << ": ";
                std::cout << std::setw(15) << std::left << this->seats[i][j];
            }
            std::cout << "\n";
        }
        std::cout << "========================================\n";
    }

    void reserveSeat() {
        int seat_number = getIntFromUser("Enter seat number (1-" + std::to_string(TOTAL_SEATS) + "): ", 1, TOTAL_SEATS);
        int row = (seat_number - 1) / SEATS_PER_ROW;
        int col = (seat_number - 1) % SEATS_PER_ROW;
        
        if (this->seats[row][col] != "Empty") {
            std::cout << "Seat " << seat_number << " is already booked by " << this->seats[row][col] << "!\n";
        } else {
            std::string passenger_name = getLineFromUser("Enter passenger name: ");
            if (passenger_name.empty()) {
                std::cout << "Passenger name cannot be empty. Reservation failed.\n";
            } else {
                this->seats[row][col] = passenger_name;
                std::cout << "Success! Seat " << seat_number << " reserved for " << this->seats[row][col] << ".\n";
            }
        }
    }

    void cancelReservation() {
        int seat_number = getIntFromUser("Enter seat number to cancel (1-" + std::to_string(TOTAL_SEATS) + "): ", 1, TOTAL_SEATS);
        int row = (seat_number - 1) / SEATS_PER_ROW;
        int col = (seat_number - 1) % SEATS_PER_ROW;

        if (this->seats[row][col] == "Empty") {
            std::cout << "This seat is already empty. No reservation to cancel.\n";
        } else {
            std::string old_name = this->seats[row][col];
            this->seats[row][col] = "Empty";
            std::cout << "Reservation for seat " << seat_number << " (" << old_name << ") has been successfully canceled.\n";
        }
    }

    void showPassengerList() const {
        std::cout << "\n===== Passenger List for Bus " << this->bus_no << " =====\n";
        bool has_passengers = false;
        for (int i = 0; i < TOTAL_ROWS; ++i) {
            for (int j = 0; j < SEATS_PER_ROW; ++j) {
                if (this->seats[i][j] != "Empty") {
                    int seat_number = (i * SEATS_PER_ROW) + j + 1;
                    std::cout << "Seat " << std::setw(3) << std::right << seat_number << ": " << this->seats[i][j] << "\n";
                    has_passengers = true;
                }
            }
        }
        if (!has_passengers) {
            std::cout << "No seats are currently booked on this bus.\n";
        }
        std::cout << "========================================\n";
    }

    void searchPassenger() {
        std::string name_to_find = getLineFromUser("Enter passenger name to search: ");
        bool found = false;
        for (int i = 0; i < TOTAL_ROWS; ++i) {
            for (int j = 0; j < SEATS_PER_ROW; ++j) {
                if (this->seats[i][j] == name_to_find) {
                    int seat_number = (i * SEATS_PER_ROW) + j + 1;
                    std::cout << "Passenger " << name_to_find << " found in seat " << seat_number << " on bus " << this->bus_no << ".\n";
                    found = true;
                }
            }
        }
        if (!found) {
            std::cout << "Passenger '" << name_to_find << "' was not found on this bus.\n";
        }
    }

    void showSummary() const {
        int empty_count = 0;
        int booked_count = 0;
        for (int i = 0; i < TOTAL_ROWS; ++i) {
            for (int j = 0; j < SEATS_PER_ROW; ++j) {
                if (this->seats[i][j] == "Empty") {
                    empty_count++;
                } else {
                    booked_count++;
                }
            }
        }
        std::cout << "===== Bus " << this->bus_no << " Booking Summary =====\n";
        std::cout << "Total Seats: " << TOTAL_SEATS << "\n";
        std::cout << "Booked Seats: " << booked_count << "\n";
        std::cout << "Empty Seats: " << empty_count << "\n";
        std::cout << "========================================\n";
    }
};

std::vector<Bus> buses;

Bus* findBusByNumber(const std::string& bus_number) {
    for (size_t i = 0; i < buses.size(); ++i) {
        if (buses[i].bus_no == bus_number) {
            return &buses[i];
        }
    }
    return nullptr;
}

void installBus() {
    std::cout << "\n===== Install New Bus =====\n";
    std::string bus_number = getLineFromUser("Enter new bus number: ");
    if (findBusByNumber(bus_number) != nullptr) {
        std::cout << "A bus with this number already exists. Installation failed.\n";
        return;
    }
    std::string driver_name = getLineFromUser("Enter driver name: ");
    std::string arrival_time = getLineFromUser("Enter arrival time: ");
    std::string departure_time = getLineFromUser("Enter departure time: ");
    std::string from_location = getLineFromUser("Enter origin city: ");
    std::string to_location = getLineFromUser("Enter destination city: ");

    Bus new_bus(bus_number, driver_name, arrival_time, departure_time, from_location, to_location);
    buses.push_back(new_bus);

    std::cout << "\nBus " << bus_number << " has been installed successfully!\n";
}

void showAllBuses() {
    std::cout << "\n===== All Available Buses =====\n";
    if (buses.empty()) {
        std::cout << "No buses are currently available in the system.\n";
    } else {
        for (size_t i = 0; i < buses.size(); ++i) {
            std::cout << "\n--- Bus " << i + 1 << " ---\n";
            buses[i].showBusDetails();
        }
    }
}

void searchByRoute() {
    std::cout << "\n===== Search Buses by Route =====\n";
    std::string from_location = getLineFromUser("Enter starting location: ");
    std::string to_location = getLineFromUser("Enter destination: ");

    bool found = false;
    std::cout << "\n--- Buses from " << from_location << " to " << to_location << " ---\n";
    for (const auto& bus : buses) {
        if (bus.from == from_location && bus.to == to_location) {
            bus.showBusDetails();
            found = true;
        }
    }
    if (!found) {
        std::cout << "No buses found for the specified route.\n";
    }
}

void searchByDriver() {
    std::cout << "\n===== Search Buses by Driver =====\n";
    std::string driver_name = getLineFromUser("Enter driver name to search: ");

    bool found = false;
    std::cout << "\n--- Buses driven by " << driver_name << " ---\n";
    for (const auto& bus : buses) {
        if (bus.driver == driver_name) {
            bus.showBusDetails();
            found = true;
        }
    }
    if (!found) {
        std::cout << "No buses found for this driver.\n";
    }
}

void adminMenu(int& adminChoice) {
    std::cout << "\n===== Admin Menu =====" << std::endl;
    std::cout << "1. Install New Bus" << std::endl;
    std::cout << "2. Search for Passenger on a Bus" << std::endl;
    std::cout << "3. Show Booking Summary for a Bus" << std::endl;
    std::cout << "4. Show Passenger List for a Bus" << std::endl;
    std::cout << "5. Search Bus by Driver" << std::endl;
    std::cout << "6. Logout" << std::endl;
    adminChoice = getIntFromUser("Enter choice: ", 1, 6);

    std::string bus_number_input;
    switch (adminChoice) {
        case 1:
            installBus();
            break;
        case 2:
            // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            bus_number_input = getLineFromUser("Enter bus number to search for a passenger: ");
            if (Bus* bus = findBusByNumber(bus_number_input)) {
                bus->searchPassenger();
            } else {
                std::cout << "Bus not found.\n";
            }
            break;
        case 3:
            // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            bus_number_input = getLineFromUser("Enter bus number to view summary: ");
            if (Bus* bus = findBusByNumber(bus_number_input)) {
                bus->showSummary();
            } else {
                std::cout << "Bus not found.\n";
            }
            break;
        case 4:
            // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            bus_number_input = getLineFromUser("Enter bus number to view passenger list: ");
            if (Bus* bus = findBusByNumber(bus_number_input)) {
                bus->showPassengerList();
            } else {
                std::cout << "Bus not found.\n";
            }
            break;
        case 5:
            searchByDriver();
            break;
        case 6:
            std::cout << "Logging out...\n";
            break;
        default:
            std::cout << "Invalid choice!\n";
    }
}

void customerMenu(int& customerChoice) {
    std::cout << "\n===== Customer Menu =====" << std::endl;
    std::cout << "1. Show All Buses" << std::endl;
    std::cout << "2. Reserve a Seat on a Bus" << std::endl;
    std::cout << "3. Cancel a Reservation on a Bus" << std::endl;
    std::cout << "4. Show Seat Arrangement for a Bus" << std::endl;
    std::cout << "5. Search Bus by Route" << std::endl;
    std::cout << "6. Logout" << std::endl;
    customerChoice = getIntFromUser("Enter choice: ", 1, 6);

    std::string bus_number_input;
    switch (customerChoice) {
        case 1:
            showAllBuses();
            break;
        case 2:
            // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            bus_number_input = getLineFromUser("Enter bus number to reserve a seat on: ");
            if (Bus* bus = findBusByNumber(bus_number_input)) {
                bus->reserveSeat();
            } else {
                std::cout << "Bus not found.\n";
            }
            break;
        case 3:
            // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            bus_number_input = getLineFromUser("Enter bus number to cancel a reservation on: ");
            if (Bus* bus = findBusByNumber(bus_number_input)) {
                bus->cancelReservation();
            } else {
                std::cout << "Bus not found.\n";
            }
            break;
        case 4:
            // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            bus_number_input = getLineFromUser("Enter bus number to view seat arrangement: ");
            if (Bus* bus = findBusByNumber(bus_number_input)) {
                bus->showSeats();
            } else {
                std::cout << "Bus not found.\n";
            }
            break;
        case 5:
            searchByRoute();
            break;
        case 6:
            std::cout << "Logging out...\n";
            break;
        default:
            std::cout << "Invalid choice!\n";
    }
}

int main() {
    User::Role currentUserRole;
    int mainMenuChoice;
    bool exitProgram = false;

    do {
        std::cout << "\n===== Main Menu =====" << std::endl;
        std::cout << "1. Admin Login" << std::endl;
        std::cout << "2. Customer Access" << std::endl;
        std::cout << "3. Exit Program" << std::endl;
        mainMenuChoice = getIntFromUser("Enter choice: ", 1, 3);

        switch (mainMenuChoice) {
            case 1: {
                std::string password = getLineFromUser("Enter admin password: ");
                if (password == "5827") {
                    currentUserRole = User::ADMIN;
                    std::cout << "Admin login successful.\n";
                    int adminChoice;
                    do {
                        adminMenu(adminChoice);
                    } while (adminChoice != 6);
                } else {
                    std::cout << "Incorrect password.\n";
                }
                break;
            }
            case 2: {
                currentUserRole = User::CUSTOMER;
                std::cout << "Customer access granted.\n";
                int customerChoice;
                do {
                    customerMenu(customerChoice);
                } while (customerChoice != 6);
                break;
            }
            case 3:
                std::cout << "Exiting program...\n";
                exitProgram = true;
                break;
            default:
                std::cout << "Invalid choice!\n";
        }
    } while (!exitProgram);

    return 0;
}