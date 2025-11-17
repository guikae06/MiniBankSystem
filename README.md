# MiniBankSystem - Basic

## Build (Qt Creator)
1. Open `MiniBankSystem.pro` in Qt Creator.
2. Configure kit if prompted.
3. Build → Rebuild Project.
4. Run.

## Features (basic)
- Abstract `Account` base class
- `SavingsAccount` (interest)
- `CheckingAccount` (overdraft + fee)
- `MiniBank` holds accounts (smart pointers)
- GUI (Qt) for deposit, withdraw, add interest
- Autosave to `accounts.csv`

## Notes
- After you change `mainwindow.ui`, do Clean & Rebuild.
- Uses C++17.
