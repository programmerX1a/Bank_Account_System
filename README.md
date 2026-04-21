# Bank Account Management System

A comprehensive C application for managing bank accounts with features like account creation, fund transfers, deposits/withdrawals, and advanced account querying.

## Features

✨ **Core Functionality:**
- User authentication and login system
- Create and manage bank accounts
- Deposit and withdraw funds with daily limits
- Transfer money between accounts
- Query and search account information
- Advanced search capabilities

📊 **Account Management:**
- Add new accounts with personal information
- Modify existing account details
- Delete single or multiple accounts
- Filter accounts by activity and date
- Change account status

🔍 **Reporting & Analysis:**
- Sort accounts by balance, creation date, or name
- Generate comprehensive account reports
- Print account information with color-coded output
- Load and display all accounts

## Project Structure

```
.
├── main.c                          # Entry point with menu system
├── OurFunctions.c                  # Core function implementations
├── OurFunctions.h                  # Function declarations
├── oijij.cbp                       # CodeBlocks project file
├── accounts.txt                    # Account data storage
├── users.txt                       # User credentials
├── README.md                       # This file
└── Programming-Project-Report.pdf  # Detailed documentation
```

## Getting Started

### Prerequisites

- **Compiler:** GCC or any C compiler
- **OS:** Windows/Linux with terminal support
- **IDE (MUST):** CodeBlocks

### Clone or Download

1. Download or clone this repository
2. Ensure all source files are in the same directory

## Building

### Option 1: Using CodeBlocks (MUST)
1. Open `oijij.cbp` in CodeBlocks
2. Click **Build** → **Build Project**
3. The executable will be in the `bin/Debug/` folder

### Option 2: Using Command Line

```bash
gcc main.c OurFunctions.c -o bank_system
```

## Running

### Via CodeBlocks
- Click **Build** → **Run** or press **F9**

### Via Command Line
```bash
./bank_system        # Linux/Mac
bank_system.exe      # Windows
```

## Data Files

| File | Purpose |
|------|---------|
| `accounts.txt` | Stores all bank account records (account number, name, email, balance, phone, creation date, status) |
| `users.txt` | Stores admin/user login credentials |
| `(user's number).txt` | Stores the transactions made for specific users |

**Format (accounts.txt):**
```
[AccountNumber],[Name],[Email],[Balance],[Mobile],[Month]-[Year],[Status]
```

## Usage Guide

Upon running the program, you'll see a menu with options:

1. **Login** - Authenticate as an admin user
2. **Add Account** - Create a new bank account
3. **Query Account** - Search for specific account
4. **Withdraw** - Withdraw funds (respects daily limits)
5. **Deposit** - Add funds to an account
6. **Transfer** - Move money between accounts
7. **Modify Account** - Update account information
8. **Delete Account** - Remove an account
9. **Generate Report** - View account statistics
10. **Exit** - Save and quit

## Functions Overview

### Account Operations
- `addAccount()` - Create new accounts
- `deleteAccount()` - Remove single account
- `deleteMultiple()` - Remove multiple accounts at once
- `modifyAccount()` - Update account details
- `changeStatus()` - Change account status

### Transactions
- `Deposit()` - Add funds to account
- `Withdraw()` - Remove funds with daily limit check
- `Transfer()` - Transfer money between accounts

### Search & Query
- `Query()` - Find and display account details
- `Advanced_Search()` - Search by multiple criteria
- `accData()` - Retrieve account balance

### Sorting & Reporting
- `sortByBalance()` - Order accounts by balance
- `sortByDate()` - Order accounts by creation date
- `sortByName()` - Order accounts alphabetically
- `Report()` - Generate comprehensive report
- `Print()` - Display formatted account information

### System Functions
- `Login()` - User authentication
- `Load()` - Load accounts from file
- `Save()` - Save accounts to file
- `Menu()` - Display main menu
- `Quit()` - Exit program

## Documentation

For detailed information including:
- Test cases and test results
- Function parameters and return values
- Code examples and usage scenarios
- System requirements and limitations

📖 **Please refer to:** `Programming-Project-Report.pdf`

## Notes

- Account balances are stored as floating-point numbers
- The system uses ANSI color codes for terminal output (compatible with Windows 10+)
- Daily withdrawal limits are enforced per account
- All data is stored in plain text files in the current directory
- The program implements error handling for invalid inputs

**Last Updated:** April 2026

