# MiniBankSystem

A simple Qt-based banking application demonstrating **object-oriented programming** concepts in C++, including:

- **Inheritance** and **polymorphism**
- **Virtual functions**
- **Thread-safe operations**
- **File saving and autosave**

This project manages **checking and savings accounts**, allowing deposits, withdrawals, and interest application for savings accounts.

---

## Features

1. **Account Types**
   - **SavingsAccount**: Supports interest calculation.
   - **CheckingAccount**: Supports overdraft and fees.

2. **Bank Class**
   - Create and manage multiple accounts.
   - Thread-safe operations using `std::mutex`.
   - Autosave account data to file in a separate thread.
   - Find accounts by ID.

3. **GUI**
   - Built with Qt5/Qt6.
   - Deposit, withdraw, and add interest functionality.
   - Displays current balance.
   - Simple dark theme with gold accents.

4. **Safe Withdrawals**
   - Checking accounts can withdraw up to `balance + overdraft`.
   - Savings accounts cannot overdraft.

5. **File Saving**
   - Saves all accounts to a CSV file.
   - Autosave functionality every 5 seconds (configurable).

---

## Folder Structure

MiniBankSystem/
├─ Account.h
├─ CheckingAccount.h
├─ SavingsAccount.h
├─ Bank.h
├─ Account.cpp
├─ CheckingAccount.cpp
├─ SavingsAccount.cpp
├─ Bank.cpp
├─ main.cpp
├─ mainwindow.h
├─ mainwindow.cpp
├─ mainwindow.ui
├─ README.md
└─ MiniBankSystem.pro


---

## How to Build

1. **Install Qt5/Qt6** on your system.
2. Open the project in **Qt Creator**.
3. Run **qmake** to generate the Makefile (usually automatic).
4. Build and run.

Or via command line:

```bash
qmake MiniBankSystem.pro
make
./MiniBankSystem

