# 🚌 Bus Reservation System (C++)

## 📌 Overview
This is a **menu-driven C++ Bus Reservation System** that allows users to install buses, reserve seats, cancel tickets, and view seat arrangements.  
The system has been upgraded with:
- **Seat Map View** – Shows available seats by number and booked seats as `X`.
- **Booking ID Generation** – Creates a unique ID for every reservation.
- **Cancel Ticket by Booking ID** – Cancel seats securely using a booking ID.

It’s fully interactive, making it simple for passengers and admins to manage reservations in real time.

---

## ✨ Features
1. **Install Bus** – Add bus details like bus number, driver name, arrival & departure time, and route.
2. **Show All Buses** – View details of all installed buses.
3. **Reserve Seat** – Book a seat, store passenger name, and generate a unique booking ID.
4. **Cancel Ticket (Booking ID)** – Cancel a reserved seat using its booking ID.
5. **Show Seat Map** – Display available seats and booked seats visually.
6. **Menu-Driven Interface** – Easy to navigate with numbered options.

---

## 📂 File Structure
├── bus_reservation.cpp # Main C++ source code
├── README.md # Project documentation


---

## 🛠️ How to Run
1. **Compile the program**
   ```bash
   g++ bus_reservation.cpp -o bus_reservation
2.**  Run the program**

./bus_reservation


💻 **Example Usage**

===== Bus Reservation Menu =====
1. Install Bus
2. Show All Buses
3. Reserve Seat
4. Cancel Ticket (Booking ID)
5. Show Seat Map
6. Exit
Enter choice: 1
Enter bus number: MH12AB1234
Enter driver name: John
Enter arrival time: 08:00
Enter departure time: 14:00
From: Pune
To: Mumbai
✅ Bus Installed Successfully!



