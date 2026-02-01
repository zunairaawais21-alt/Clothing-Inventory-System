Garment Store Management System 👔👗
A comprehensive C++ console application developed as my first-semester final project. This system manages a clothing store's inventory and sales, featuring a dual-user interface for Admins and Customers with persistent data storage.

🚀 Overview
This project simulates a real-world retail environment. It handles everything from stock procurement and profit analysis to customer shopping carts and digital receipts. The core focus was to implement CRUD operations and File I/O using C++.

✨ Key Features
👤 Admin Module
Inventory Management: Add, update, and delete garments from the system.

Profit/Loss Reports: Real-time calculation of unit costs, total profit, and potential losses based on wholesale and shipping costs.

Stock Tracking: Monitor "Stock Left" versus "Stock Needed" automatically.

Customer Overview: View the purchase history and credentials of all registered users.

🛒 Customer Module
Category Browsing: Filter garments by type (e.g., shirts, pants, jackets).

Smart Shopping Cart: Add or remove items from a cart before finalizing the purchase.

Dynamic Discounts: * Day-based: 10% off on Sundays, 5% off on Saturdays.

Bundle Offer: "Buy 2 Get 1 Free" logic automatically applied to the cheapest items in the cart.

Receipt Generation: Provides a detailed breakdown of items, discounts, and change due.

💾 Technical Highlights
Persistent Storage: Data is saved to GarmentStore.txt using custom parsing logic to ensure data persists after the program closes.

Sorting Algorithm: Uses Selection Sort to organize inventory based on unit availability.

Security: Password-protected login system with role-based access control (Admin vs. User).

UI/UX: Enhanced console experience using color-coded text and formatted tables.

🛠️ Built With
Language: C++

Libraries: iostream, fstream, iomanip, string

Platform: Windows (utilizes windows.h and conio.h)

📥 How to Run
Clone the repository:

Bash
git clone https://github.com/zunairaawais21-alt/Clothing-Inventory-System.git
Compile: Use a C++ compiler (like MinGW/GCC or Visual Studio).

Bash
g++ business.cpp -o GarmentStore.exe
Run:

Bash
./GarmentStore.exe
