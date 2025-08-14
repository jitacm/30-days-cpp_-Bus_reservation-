#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
#include <map>
#include <fstream>
#include <sstream>
#include "user.h"

// Define constants for magic numbers
const int TOTAL_ROWS = 8;
const int SEATS_PER_ROW = 4;
const int TOTAL_SEATS = TOTAL_ROWS * SEATS_PER_ROW;

// Global vector to hold bus objects
std::vector<Bus> buses;

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

// Functions for saving and loading all buses
void saveAllBuses() {
    std::ofstream out("buses.txt");
    if (!out.is_open()) {
        std::cerr << "Error: Could not open buses.txt for writing.\n";
        return;
    }
    out << buses.size() << '\n';
    for (auto &bus : buses) {
        out << bus.bus_no << '\n';
        out << bus.driver << '\n';
        out << bus.arrival << '\n';
        out << bus.departure << '\n';
        out << bus.from << '\n';
        out << bus.to << '\n';
        for (int i = 0; i < TOTAL_ROWS; ++i) {
            for (int j = 0; j < SEATS_PER_ROW; ++j) {
                out << bus.seats[i][j] << '\n';
            }
        }
    }
    out.close();
}

void loadAllBuses() {
    std::ifstream in("buses.txt");
    if (!in.is_open()) {
        // File doesn't exist, start with an empty system
        return;
    }
    int n;
    in >> n;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (int i = 0; i < n; ++i) {
        std::string bno, drv, arr, dep, from, to;
        std::getline(in, bno);
        std::getline(in, drv);
        std::getline(in, arr);
        std::getline(in, dep);
        std::getline(in, from);
        std::getline(in, to);
        Bus b(bno, drv, arr, dep, from, to);
        for (int row = 0; row < TOTAL_ROWS; ++row) {
            for (int col = 0; col < SEATS_PER_ROW; ++col) {
                std::getline(in, b.seats[row][col]);
            }
        }
        buses.push_back(b);
    }
    in.close();
}

Bus* findBusByNumber(const std::string& bus_number) {
    for (size_t i = 0; i < buses.size(); ++i) {
        if (buses[i].bus_no == bus_number) {
            return &buses[i];
        }
    }
    return nullptr;
}

// New login function
User* loginUser() {
    std::string username = getLineFromUser("Enter username: ");
    std::string password = getLineFromUser("Enter password: ");
    
    return User::authenticate(username, password);
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
    saveAllBuses();
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
            bus_number_input = getLineFromUser("Enter bus number to search for a passenger: ");
            if (Bus* bus = findBusByNumber(bus_number_input)) {
                bus->searchPassenger();
            } else {
                std::cout << "Bus not found.\n";
            }
            break;
        case 3:
            bus_number_input = getLineFromUser("Enter bus number to view summary: ");
            if (Bus* bus = findBusByNumber(bus_number_input)) {
                bus->showSummary();
            } else {
                std::cout << "Bus not found.\n";
            }
            break;
        case 4:
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
            bus_number_input = getLineFromUser("Enter bus number to reserve a seat on: ");
            if (Bus* bus = findBusByNumber(bus_number_input)) {
                bus->reserveSeat();
                saveAllBuses();
            } else {
                std::cout << "Bus not found.\n";
            }
            break;
        case 3:
            bus_number_input = getLineFromUser("Enter bus number to cancel a reservation on: ");
            if (Bus* bus = findBusByNumber(bus_number_input)) {
                bus->cancelReservation();
                saveAllBuses();
            } else {
                std::cout << "Bus not found.\n";
            }
            break;
        case 4:
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
    loadAllBuses(); // Load bus data at startup
    User::initializeUsers(); // Load user data at startup
    
    int mainMenuChoice;
    bool exitProgram = false;

    do {
        std::cout << "\n===== Main Menu =====" << std::endl;
        std::cout << "1. Login" << std::endl;
        std::cout << "2. Exit Program" << std::endl;
        mainMenuChoice = getIntFromUser("Enter choice: ", 1, 2);

        switch (mainMenuChoice) {
            case 1: {
                User* loggedInUser = loginUser();
                if (loggedInUser) {
                    std::cout << "Login successful. Welcome, " << loggedInUser->username << "!\n";
                    if (loggedInUser->getRole() == User::ADMIN) {
                        int adminChoice;
                        do {
                            adminMenu(adminChoice);
                        } while (adminChoice != 6);
                    } else if (loggedInUser->getRole() == User::CUSTOMER) {
                        int customerChoice;
                        do {
                            customerMenu(customerChoice);
                        } while (customerChoice != 6);
                    }
                } else {
                    std::cout << "Login failed. Invalid username or password.\n";
                }
                break;
            }
            case 2:
                std::cout << "Exiting program...\n";
                exitProgram = true;
                break;
            default:
                std::cout << "Invalid choice!\n";
        }
    } while (!exitProgram);

    return 0;
}