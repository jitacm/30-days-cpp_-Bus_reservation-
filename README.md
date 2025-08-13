### 🚍 Bus Reservation System

This is a comprehensive C++ console application for managing bus reservations. The project serves as a practical demonstration of fundamental programming concepts, including Object-Oriented Programming (OOP), the use of dynamic data structures like `std::vector`, and file handling for data persistence. It's an excellent example for a computer science and engineering student to showcase skills in designing and building a functional, interactive system from the ground up.

-----

### 🌟 Project Features in Detail

The system is designed with distinct user roles and robust features to handle various scenarios:

  * **User Roles**: The program features a user authentication system that separates privileges. An **Admin** has access to all management features, while a **Customer** can only perform actions related to their own reservations. This improves security and provides a cleaner, more intuitive user interface by showing only relevant options to each user type.
  * **Bus Management**: The "Install a new bus" feature allows administrators to add new bus entries to the system. This involves specifying essential details such as the bus's unique number, the driver's name, the route (from and to locations), and the travel timings (arrival and departure).
  * **Reservation System**: Customers can easily reserve seats on any available bus. They can also cancel existing reservations by entering the bus number and seat number, making the booking process flexible. The system handles scenarios where a seat is already booked or a reservation is non-existent.
  * **Visual Seat Arrangement**: The application can display a clear visual representation of a bus's seating layout. This helps users quickly see which seats are available and which are already booked.
  * **Search Functionality**: A dedicated search feature allows users to quickly find a specific bus by its unique number. This is a crucial feature for a reservation system, as it provides quick access to bus details.
  * **Booking Summary**: Administrators can access a summary that shows the total number of booked and empty seats for any given bus, providing a quick and clear overview of bus occupancy.
  * **Data Persistence**: All bus and reservation data is automatically saved to a text file named `buses.txt`. When the program is run again, it automatically loads this data, ensuring that no information is lost between sessions. This is achieved using C++ file I/O streams (`fstream`).

-----

### 🚀 Getting Started

To get the project up and running on your local machine, follow these steps.

#### Prerequisites

You will need a C++ compiler installed on your system. `g++` is a widely-used and recommended option, and it's part of the GCC (GNU Compiler Collection).

  * **Windows**: Install a compiler like MinGW or use the one provided with Visual Studio.
  * **macOS**: Install Xcode Command Line Tools.
  * **Linux**: Install `g++` using your distribution's package manager (e.g., `sudo apt-get install g++`).

#### Installation

1.  Clone the project repository from GitHub to your local machine:
    ```bash
    git clone https://github.com/Ashleesh/30-days-cpp_-Bus_reservation-.git
    ```
2.  Navigate to the project directory:
    ```bash
    cd 30-days-cpp_-Bus_reservation-/bus-reservation-system
    ```

-----

### 🛠️ Build and Run

The project is structured into multiple files to promote good design practices. You need to compile all source files together to create a single executable.

#### Compiling the Code

Open your terminal in the project directory and use the `g++` compiler.

```bash
g++ main.cpp user.cpp -o bus_reservation.exe
```

  * `g++`: The C++ compiler.
  * `main.cpp user.cpp`: The source files to be compiled.
  * `-o bus_reservation.exe`: The output flag, which names the final executable file `bus_reservation.exe`.

#### Running the Application

After the executable is created, you can run the program from your terminal.

  * On **Windows**, run the executable directly:
    ```bash
    .\bus_reservation.exe
    ```
  * On **Linux** or **macOS**, run the executable with `./`:
    ```bash
    ./bus_reservation.exe
    ```

-----

### 📂 Project Structure

The project is organized into the following files to maintain modularity and clarity:

  * `main.cpp`: This is the main application file. It contains the program's primary logic, the user interface menus, and function calls to the `Bus` and `User` classes.
  * `user.h`: This is a header file that defines the `User` class. It declares the class structure, member variables (like username, password, and role), and methods for user authentication.
  * `user.cpp`: This is the implementation file for the `User` class. It contains the actual code for the methods declared in `user.h`, including the logic for validating a user's password.
  * `buses.txt`: This is a plain text file that is automatically created and managed by the program to store all bus and reservation data. It ensures that the state of the application is saved even after the program is closed.

-----

### 💻 Usage and Functionality

The application runs in your console and guides you through a series of menus based on your access level.

#### Main Menu

When you first run the program, you will be prompted to choose your access level.

1.  **Admin Login**: Choose this option to access administrative features. You will be asked for a password to proceed.
2.  **Customer Access**: Choose this option to immediately access customer-related features.
3.  **Exit Program**: This option cleanly shuts down the application.

#### Admin Menu

After a successful admin login, you can perform administrative tasks:

  * **Install New Bus**: Add a new bus with its details (bus number, driver, route, and timings).
  * **Search for Passenger**: Find a passenger by name and see their booking details.
  * **Show Booking Summary**: View a summary of booked and empty seats for a specific bus.
  * **Logout**: Return to the main menu.

#### Customer Menu

As a customer, you can:

  * **Show All Buses**: View a list of all buses currently in the system.
  * **Reserve a Seat**: Book an available seat on a bus of your choice.
  * **Cancel a Reservation**: Cancel a previously booked seat.
  * **Show Seat Arrangement**: View a seat map for a specific bus.
  * **Logout**: Return to the main menu.

-----

### 📄 License

This project is licensed under the MIT License—feel free to use and modify it.