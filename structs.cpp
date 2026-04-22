#include <iostream>
#include <fstream>
#include <cstring>
#include <limits>

using namespace std;

struct Teller
{
    char id[10];
    char name[32];
    char password[20];
    char branch[10];
};

struct Customer
{
    char accountNumber[10];
    char name[32];
    char pin[6];
    double balance;
    char branch[10];
};

struct Transaction
{
    char accountNumber[10];
    char type[20];
    double amount;
    char targetAccount[10];
};

void saveTransaction(const char accNum[], const char transType[], double amount, const char targetAcc[]);

void createTeller()
{
    Teller t;

    strcpy(t.id, "T001");
    strcpy(t.name, "Admin");
    strcpy(t.password, "1234");
    strcpy(t.branch, "CPT");

    ofstream f("tellers.dat", ios::binary);

    if (!f)
    {
        cout << "File error" << endl;
        return;
    }

    f.write((char *)&t, sizeof(t));
    f.close();

    cout << "Default user created" << endl;
}

void readTeller()
{
    Teller t;

    ifstream f("tellers.dat", ios::binary);

    if (!f)
    {
        cout << "File error!" << endl;
        return;
    }

    while (f.read((char *)&t, sizeof(t)))
    {
        cout << "ID: " << t.id << endl;
        cout << "Name: " << t.name << endl;
        cout << "Password: " << t.password << endl;
        cout << "Branch: " << t.branch << endl;
    }

    f.close();
}

bool loginTeller()
{
    char inputID[10];
    char inputPassword[20];
    int attempts = 0;

    Teller t;

    while (attempts < 3)
    {
        cout << "Teller Login" << endl;
        cout << "Enter Teller ID" << endl;
        cin >> inputID;
        cout << "Enter Password" << endl;
        cin >> inputPassword;

        ifstream f("tellers.dat", ios::binary);

        if (!f)
        {
            cout << "File Error!" << endl;
            return false;
        }

        while (f.read((char *)&t, sizeof(t)))
        {
            if (strcmp(t.id, inputID) == 0 && strcmp(t.password, inputPassword) == 0)
            {
                cout << "Login Successful" << endl;
                cout << "Welcome " << t.name << " from branch " << t.branch << endl;
                f.close();
                return true;
            }
        }

        f.close();
        attempts++;
        cout << "Invalid Teller ID or Password" << endl;
        cout << "Attempts left: " << 3 - attempts << endl;
    }

    cout << "Too many failed attempts. Account locked!" << endl;
    return false;
}

void createCustomer()
{
    Customer c;

    cout << "\nCreate Customer Account" << endl;
    cout << "Enter Account Number" << endl;
    cin >> c.accountNumber;
    cout << "Enter Customer Name" << endl;
    cin >> c.name;
    cout << "Enter PIN (5-Digit)" << endl;
    cin >> c.pin;
    cout << "Enter Opening Balance" << endl;
    cin >> c.balance;
    cout << "Enter Branch Code" << endl;
    cin >> c.branch;

    ofstream f("customers.dat", ios::binary | ios::app);

    if (!f)
    {
        cout << "File Error!";
        return;
    }

    f.write((char *)&c, sizeof(c));
    f.close();

    cout << "Customer Account created successfully!" << endl;
}

void readCustomer()
{
    Customer c;

    ifstream f("customers.dat", ios::binary);

    if (!f)
    {
        cout << "File Error!" << endl;
        return;
    }

    while (f.read((char *)&c, sizeof(c)))
    {
        cout << "\nAccount Number: " << c.accountNumber << endl;
        cout << "Name: " << c.name << endl;
        cout << "Pin: " << c.pin << endl;
        cout << "Balance: " << c.balance << endl;
        cout << "Branch: " << c.branch << endl;
    }

    f.close();
}

bool loginCustomer(Customer &loggedIn)
{
    Customer c;

    char inputAcc[10];
    char inputPin[6];
    int attempts = 0;

    while (attempts < 3)
    {
        cout << "\nCustomer Account Login" << endl;
        cout << "Enter Account number" << endl;
        cin >> inputAcc;
        cout << "Enter your PIN" << endl;
        cin >> inputPin;

        ifstream f("customers.dat", ios::binary);

        if (!f)
        {
            cout << "File Error!" << endl;
            return false;
        }
        while (f.read((char *)&c, sizeof(c)))
        {
            if (strcmp(c.accountNumber, inputAcc) == 0 && strcmp(c.pin, inputPin) == 0)
            {
                cout << "Login Successful!" << endl;
                cout << "Welcome " << c.name << endl;
                loggedIn = c;
                f.close();
                return true;
            }
        }
        f.close();
        attempts++;
        cout << "Invalid Account number or PIN!" << endl;
        cout << "Attempts remaining: " << 3 - attempts << endl;
    }
    cout << "Too many failed attempts! Account locked!" << endl;
    return false;
}

void transfer(Customer &c){

    char targetAcc[10];
    double amount;
    Customer target;
    bool found = false;

    cout << "Enter target account number: ";
    cin >> targetAcc;

    if(strcmp(targetAcc, c.accountNumber) == 0){
        cout << "You can't transfer to your own account!" << endl;
        return;
    }

    cout << "Enter amount to transfer: ";
    cin >> amount;

    if(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a valid number..." << endl;
        return;
    }

    if(amount <= 0){
        cout << "Amount must be more than 0!" << endl;
        return;
    }

    if(amount > c.balance){
        cout << "Insufficient funds!" << endl;
        return;
    }
    ifstream inFile("customers.dat", ios::binary);

    if(!inFile){
        cout << "File Error" << endl;
        return;
    }

    while(inFile.read((char*)&target, sizeof(target))){
        if(strcmp(target.accountNumber, targetAcc) == 0){
            found = true;
            break;
        }
    }
    inFile.close();

    if(!found){
        cout << "Target account not found!" << endl;
        return;
    }
    c.balance -= amount;
    target.balance += amount;

    fstream f("customers.dat", ios::binary | ios::in | ios::out);

    if(!f){
        cout << "File Error!" << endl;
        return;
    }
    Customer temp;

    while(f.read((char*)&temp, sizeof(temp))){
        if(strcmp(temp.accountNumber, c.accountNumber) == 0){
            f.seekp(-sizeof(temp), ios::cur);
            f.write((char*)&c, sizeof(c));
            f.seekg(f.tellp());
        }

        else if(strcmp(temp.accountNumber , target.accountNumber) == 0){
            f.seekp(-sizeof(temp), ios::cur);
            f.write((char*)&target, sizeof( target));
            f.seekg(f.tellp());
        }
    }
    f.close();

    saveTransaction(c.accountNumber, "Transfer OUT", amount, target.accountNumber);
    saveTransaction(target.accountNumber, "Transfer IN", amount, c.accountNumber);

    cout << "Transfer Successful" << endl;
    cout << "New Balance: " << c.balance << endl;
    
}


void saveTransaction(const char accNum[], const char transType[], double amount, const char targetAcc[]){
    Transaction t;

    strcpy(t.accountNumber, accNum);
    strcpy(t.type, transType);
    t.amount = amount;
    strcpy(t.targetAccount, targetAcc);

    ofstream f("transactions.dat", ios::binary | ios::app);
    if(!f){
        cout << "Transaction file error!" << endl;
        return;
    }
    f.write((char*)&t, sizeof(t));
    f.close();
}

void viewTransactions(const Customer &c){
    Transaction t;

    bool found = false;

    ifstream f("transactions.dat", ios::binary);

    if(!f){
        cout << "No transactions file found yet" << endl;
        return;
    }

    cout << "\nTransaction history for " << c.name << endl;
    cout << "Account Number: " << c.accountNumber << endl;

    while(f.read((char*)&t, sizeof(t))){
        if(strcmp(t.accountNumber, c.accountNumber) == 0){
            cout << "Type: " << t.type << " | Amount: " << t.amount;
            if(strlen(t.targetAccount) > 0){
                cout <<" Target: " << t.targetAccount;
            }
            cout << endl;
            found = true;
        }
    }

    if(!found){
        cout << "No transactions found for this account!" << endl;
    }
    f.close();
}
void deposit(Customer &c){
    double amount;

    cout << "Enter amount to deposit: ";
    cin >> amount;

    if(cin.fail() || amount <= 0){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid amount!" << endl;
        return;
    }

    c.balance += amount;

    fstream f("customers.dat", ios::binary | ios::in | ios::out);

    if(!f){
        cout << "File Error!" << endl;
        return;
    }

    Customer temp;

    while (f.read((char*)&temp, sizeof(temp))){
        if(strcmp(temp.accountNumber, c.accountNumber) == 0){
            f.seekp(-sizeof(temp), ios::cur);
            f.write((char*)&c, sizeof(c));
            break;
        }
    }
    f.close();
    saveTransaction(c.accountNumber, "Deposit", amount,"");
    cout << "Deposit Successful! New Balance: " << c.balance << endl;
}


void withdraw(Customer &c){
    double amount;

    cout << "Enter amount to withdraw: ";
    cin >> amount;

    if(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a valid number!" << endl;
        return;
    }

    if(amount <= 0){
        cout << "Amount must be greater than 0!" << endl;
        return;
    }

    if(amount > c.balance){
        cout << "Insufficient Funds!" << endl;
        return;
    }

    c.balance -= amount;

    fstream f("customers.dat", ios::binary | ios::in | ios::out);

    if(!f){
        cout << "File Error!" << endl;
        return;
    }

    Customer temp;

    while(f.read((char*)&temp, sizeof(temp))){
        if(strcmp(temp.accountNumber, c.accountNumber) == 0){
            f.seekp(-sizeof(temp), ios::cur);
            f.write((char *)&c, sizeof(c));
            break;
        }
    }
    f.close();
    saveTransaction(c.accountNumber, "Withdraw", amount,"");
    cout << "Withdrawal Successful! New Balance: " << c.balance << endl;
}



void customerMenu(Customer &c){
    int choice;

    do{
        cout << "\nCustomer Menu\n";
        cout << "1. View Balance\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Transfer\n";
        cout << "5. View Transactions\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter number only...\n";
            choice = 0;
            continue;
        }

        switch (choice)
        {
        case 1:
            cout << "Balance: " << c.balance << endl;
            break;
        case 2:
            deposit(c);
            break;
        case 3:
            withdraw(c);
            break;
        case 4:
            transfer(c);
            break;
        case 5:
            viewTransactions(c);
            break;
        case 6:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid Option" << endl;
            break;
        }
    }while (choice != 6);
}



int main()
{
    createTeller();
    if (loginTeller())
    {
        createCustomer();
        readCustomer();

        Customer loggedIn;
        if(loginCustomer(loggedIn)){
            customerMenu(loggedIn);
        }
        
    }
    return 0;
}