# 🚍 Bus Reservation System

A simple **C++ console application** to manage bus reservations.  
This project demonstrates **OOP**, **vectors**, and **console I/O** in C++.

---

## 📑 Features

- **Install a new bus** — add bus number, driver, routes, and timings.
- **View all buses** — display details of all installed buses.
- **Reserve seats** — book any available seat (1–32) on a selected bus.
- **Visual seat arrangement** — see which seats are booked or empty.
- **Search for buses** — find buses by bus number, source, or destination for quick access.

---

## ⚙️ How to Build & Run

1. **Clone the repository**
   ```bash
   git clone https://github.com/<your-username>/<repo-name>.git
   cd <repo-name>
Compile
---------


Copy code
g++ bus.cpp -o bus
Run


Copy code
./bus


🗂️ Usage
Install a Bus
Input bus details: number, driver name, arrival & departure, source, and destination.



Show All Buses
Displays all buses with their details.

Search for Buses
Find buses by entering a bus number, source, or destination. Helps you quickly locate relevant buses.


Reserve a Seat
Select a bus and choose an available seat.


Exit
Quit the program.

✅ Example
plaintext
Copy code
===== Bus Reservation System =====
1. Install New Bus
2. Show All Buses
3. Reserve a Seat
4. Cancel a Reservation
5. Search for Buses
6. Exit
Enter choice:

🚀 Improvements
- Cancel or modify a reservation.
- Search for passengers by name.
- Save and load buses and reservations to/from files.

📄 License
This project is licensed under the MIT License — feel free to use and modify it.
