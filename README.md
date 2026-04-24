BANKING SYSTEM - C++ CONSOLE APPLICATION

OVERVIEW
This program is a console-based banking system developed in C++.
It allows teller abnd customer interactions through a menu-driven interface.
The system stores data using binary files and supports basic banking operations.

FEATURES

    1. Teller Functions: 
        - Teller Login (3 attempts allowed)
        - Create customer accounts
        - View all customers
        - Search for a customer by Account Number

    2. Customer Function:
        - Customer login (3 attempts allowed)
        - View Balance
        - Deposit Money
        - Withdraw Money
        - Transfer Funds to another account
        - View Transactions History

    3. Transaction System:
        - All deposits, withdrawals, and transfers are recorded
        - Transactions are stored in a binary file
        - Each customer can view transaction history
        
    4. Password & PIN Encryption
        - Teller passwords and customer PINs are encrypted before being stored
        - User input is encrtpyed during login and compared with stroed data
        - This ensures sensitive information is not stored in plain text

FILES USED
    - tellers.dat   -> Stores tellers login details
    - customers.dat -> Stores customer account information
    - transactions.dat  -> Stores transaction records

STRUCTURES USED
    - Teller 
        Stores teller ID, name, password and branch
    - Customer
        Stores account number, name, PIN, balance and branch
    - Transaction
        Stores account number, transaction type, account and target account

HOW TO RUN
    1. Open a C++ compiler (e.g Dev C++, Codeblocks or g++)
    2. Compile the program:
        g++ bank.cpp -o bank
    3. Run the program:
        ./bank

PROGRAM FLOW

    1. Main Menu
        - Teller login
        - Customer login
        - Exit

    2. Teller Menu
        - Create customer
        - View customer
        - Search customer
        - Logout

    3. Customer Menu
        - View Balance
        - Deposit
        - Withdraw
        - Transfer
        - View Transaction 
        - Exit
    
NOTES
    - A default teller is created automatically if none exists: 
        ID: T001
        Password: 1234
    - Customer must use their account numbers and PIN to log in
    - Input validation is implement to prevent invalid entries
    - Files are stored in binary format for efficiency

LIMITATIONS
    - No graphical user interface (console-based only)
    - No advanced security (Simple encryption used)
    - No account deletion or update functionality

CONCLUSION
    This system demonstrates the use of file handling, structures and menu-driven programming in C++.
    It simulates basic banking operations and ensures data persistence through binary file storage