# 🚍 Bus Reservation System

A simple **C++ console application** to manage bus reservations.  
This project demonstrates **OOP**, **vectors**, **file I/O**, and **console interaction** in C++.

---

# 🚍 Bus Reservation System

A simple **C++ console application** to manage bus reservations.  
This project demonstrates **OOP**, **vectors**, **file I/O**, and **console interaction** in C++.

---

## 📁 Features

- **Install a new bus** — Add bus number, driver, routes, and timings.
- **View all buses** — Display details of all installed buses.
- **Reserve seats** — Book any available seat (1–32) on a selected bus.
- **Visual seat arrangement** — See which seats are booked or empty.
- **Cancel reservation** — Cancel a seat reservation by number.
- **Search bus by number** — Quickly look up a specific bus.
- **List reserved seats** — View all reserved seats and passenger names.
- **Save & load data** — Bus and seat data is saved to a file (`buses.txt`) and reloaded automatically on program start.

---

## ⚙️ How to Build & Run

1. **Clone the repository**
   ```bash
   git clone https://github.com/<your-username>/30-days-cpp_-Bus_reservation-.git
   cd 30-days-cpp_-Bus_reservation-

## ⚙️ How to Build & Run

1. **Clone the repository**
   ```bash
   git clone https://github.com/<your-username>/30-days-cpp_-Bus_reservation-.git
   cd 30-days-cpp_-Bus_reservation-
   ```

2. **Compile**
   ```bash
   g++ bus.cpp -o bus
   ```

3. **Run**
   ```bash
   ./bus
   ```


## 🗂️ Usage

### Install a Bus
Input bus details: number, driver name, arrival & departure time, source, and destination.

### Show All Buses
Displays all installed buses with details.

### Reserve a Seat
Enter a bus number and choose an available seat.

### Cancel Reservation
Enter bus number and seat number to cancel a booking.

### Search Bus by Number
Search and view details of a bus by entering its number.

### View Seat Arrangement
View the full seat layout of a selected bus.

### List Reserved Seats
See which seats are booked and the corresponding passenger names.

### Exit
Exit the program.

---

## ✅ Example
```plaintext
===== Bus Reservation System =====
1. Install New Bus
2. Show All Buses
3. Reserve a Seat
4. Cancel a Reservation
5. Search Bus by Number
6. View Seat Arrangement
7. List Reserved Seats
8. Exit
Enter choice:
```

---

## 📄 License
This project is licensed under the MIT License — feel free to use and modify it.
