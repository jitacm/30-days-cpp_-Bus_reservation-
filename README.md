🚍 Bus Reservation System: A Comprehensive C++ Console Application
This is a comprehensive C++ console application for managing a bus reservation system. The project demonstrates core programming principles like Object-Oriented Programming (OOP) through classes such as Bus and User, the use of dynamic data structures like std::vector for flexible data storage, and robust file handling for data persistence. It serves as an excellent portfolio project for a computer science student, showcasing the ability to build a functional and interactive system from scratch.

🌟 Current Project Features in Detail
The system has been developed with distinct user roles and a wide range of features to handle various scenarios:


User Roles & Secure Authentication: The program now features a secure user authentication system. It separates privileges between an 

Admin and a Customer. An Admin has access to all management features, while a Customer can only perform actions related to their own reservations. The system also includes password hashing, ensuring that passwords are never stored in plain text. User credentials are saved to a 

users.txt file, which is loaded on startup and allows for multiple user accounts.


Bus Management: The "Install a new bus" feature enables administrators to add new buses to the system by specifying essential details like a unique bus number, driver's name, route (from and to locations), and travel timings (arrival and departure).

Reservation System: Customers can easily reserve and cancel seats on any available bus. The system includes validation to prevent booking a seat that is already taken.

Visual Seat Arrangement: The application can display a clear visual representation of a bus's seating layout. This helps users quickly identify which seats are booked and which are available.

Search Functionality: The system has multiple search features to improve usability:


Search Bus by Number: Users can quickly find a specific bus by entering its unique number.


Search for Passenger: Admins can find a passenger by name and view their booking details.


Search by Route: Customers can filter buses by specifying their origin and destination.


Booking Summary: Administrators can access a summary that shows the total number of booked and empty seats for any given bus, providing a quick overview of its occupancy.


Data Persistence: All bus and reservation data is automatically saved to a text file named buses.txt. This ensures that the application's state is preserved even after the program is closed. The data is automatically loaded when the program starts again.

Dynamic Ticket ID: The system can generate a unique and permanent ticket ID for each successful reservation. This provides customers with a verifiable booking reference that can be used for future inquiries or verification.

🚀 Getting Started
To get the project up and running on your local machine, follow these detailed steps.

Prerequisites
You will need a C++ compiler installed on your system. g++ is a widely-used and recommended option, and it's part of the GCC (GNU Compiler Collection).

Windows:

MinGW: Download and install the MinGW-w64 toolchain. Ensure that the bin directory is added to your system's PATH environment variable. You can verify the installation by opening the Command Prompt and typing g++ --version.

Visual Studio: Install Visual Studio with the "Desktop development with C++" workload, which includes the MSVC compiler.

macOS:

Install Xcode Command Line Tools by running xcode-select --install in your terminal. This will provide you with the g++ compiler.

Linux:

Install g++ using your distribution's package manager. For Debian/Ubuntu-based systems, use sudo apt-get update && sudo apt-get install build-essential.

Installation
Clone the project repository from GitHub to your local machine:

Bash

git clone https://github.com/Ashleesh/30-days-cpp_-Bus_reservation-.git
Navigate to the project directory:

Bash

cd 30-days-cpp_-Bus_reservation-/bus-reservation-system
🛠️ Build and Run
The project is structured into multiple files to promote good design practices. You need to compile all source files together to create a single executable.

Compiling the Code
Open your terminal in the project directory and use the g++ compiler to compile the main.cpp and user.cpp files.

Bash

g++ main.cpp user.cpp -o bus_reservation.exe
g++: The C++ compiler.

main.cpp user.cpp: The source files to be compiled.

-o bus_reservation.exe: The output flag, which names the final executable file bus_reservation.exe.

Running the Application
After the executable is created, you can run the program from your terminal.

On Windows, run the executable directly:

Bash

.\bus_reservation.exe
On Linux or macOS, run the executable with ./:

Bash

./bus_reservation.exe
📂 Project Structure
The project is organized into the following files to maintain modularity and clarity:

main.cpp: This is the core application file. It contains the main program logic, the user interface menus, and function calls to the Bus and User classes.

user.h: This header file defines the User class, declaring its structure, member variables (like username, and role), and methods for user authentication. It also declares static functions for password hashing and user management.

user.cpp: This is the implementation file for the User class. It contains the actual code for the methods declared in user.h, including the logic for password hashing and file-based user authentication.

buses.txt: This is a plain text file automatically created and managed by the program to store all bus and reservation data. It ensures that the state of the application is saved even after the program is closed.

users.txt: This file is created by the program to store user credentials (username, hashed password, and role). It is fundamental to the new secure authentication feature.

💻 Usage and Functionality
The application runs in your console and guides you through a series of menus based on your access level.

Main Menu
When you first run the program, you will be prompted to log in.

Login: Enter your username and password to access the system.

Exit Program: This option cleanly shuts down the application.

Admin Menu
After a successful admin login, you can perform administrative tasks:


Install New Bus: Add a new bus with its details (bus number, driver, route, and timings).


Search for Passenger: Find a passenger by name and see their booking details.


Show Booking Summary: View a summary of booked and empty seats for a specific bus.

Show Passenger List: Get a detailed list of all passengers booked on a particular bus.

Search Bus by Driver: Find buses by searching for the driver's name.

Logout: Return to the main menu.

Customer Menu
As a customer, you can:


Show All Buses: View a list of all buses currently in the system.

Reserve a Seat: Book an available seat on a bus of your choice.


Cancel a Reservation: Cancel a previously booked seat by bus number and seat number.


Show Seat Arrangement: View a seat map for a specific bus to see which seats are available.


Search Bus by Route: Find buses by specifying your origin and destination.

Logout: Return to the main menu.

📄 License
This project is licensed under the MIT License—feel free to use and modify it ! 


Sources
