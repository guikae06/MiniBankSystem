# MiniBank Qt Application

MiniBank is a Qt-based desktop banking application written in C++ that simulates basic banking operations, insurance management, loans, and a simple stock market system. The project uses object-oriented principles, multi-threading, and file persistence to provide a complete mini banking experience.

---

## Features

### User Management
- Login using a username (no password required for simplicity)
- Automatically creates a new checking account if the username does not exist
- Display of user account information

### Account Operations
- Deposit and withdrawal of funds
- Viewing transaction history
- Support for multiple account types:
  - **Checking Account** with overdraft support
  - **Savings Account** with interest accrual

### Loans
- Request a loan with a specific amount and interest rate
- Pay back loans partially or fully
- Loan history tracking

### Insurance
- Purchase predefined insurances (Health, Car, Home)
- View owned insurances
- Funds deducted automatically when purchasing insurance

### Stock Market Simulation
- Buy and sell shares of predefined stocks
- Dynamic stock price simulation (multi-threaded)
- Portfolio overview with current value of owned shares

### Persistence
- Save and load bank data including accounts, users, loans, insurances, and transaction history

---

## Project Structure

MiniBank/
├── headers/
│ ├── Account.h
│ ├── AuthManager.h
│ ├── Bank.h
│ ├── CheckingAccount.h
│ ├── SavingsAccount.h
│ ├── StockMarket.h
│ ├── DepositWithdrawDialog.h
│ ├── LoansDialog.h
│ ├── InssuranceDialog.h
│ ├── LogInDialog.h
│ ├── MainMenuDialog.h
│ └── FileStorage.h
├── src/
│ ├── Account.cpp
│ ├── AuthManager.cpp
│ ├── Bank.cpp
│ ├── CheckingAccount.cpp
│ ├── SavingsAccount.cpp
│ ├── StockMarket.cpp
│ ├── DepositWithdrawDialog.cpp
│ ├── LoansDialog.cpp
│ ├── InssuranceDialog.cpp
│ ├── LogInDialog.cpp
│ ├── MainMenuDialog.cpp
│ └── StockMarketDialog.cpp
├── ui/
│ ├── DepositWithdrawDialog.ui
│ ├── LoansDialog.ui
│ ├── InssuranceDialog.ui
│ ├── LogInDialog.ui
│ ├── MainMenuDialog.ui
│ └── StockMarketDialog.ui
├── main.cpp
└── README.md
---

## Installation

### Requirements
- Qt 5 or Qt 6 (Qt Creator recommended)
- C++17 compatible compiler (GCC, Clang, MSVC)
- CMake 3.10+ (optional for command-line build)

### Building with Qt Creator
1. Open the project in Qt Creator.
2. Configure the kit (Desktop Qt with C++17).
3. Build and run the project.

### Building with CMake (Optional)
```bash
mkdir build
cd build
cmake ..
cmake --build .
./MiniBank
