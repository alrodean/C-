#include <iostream>
#include <fstream>
#include <cstring>

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
    char type[10];
    double amount;
};

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



void customerMenu(Customer c){
    int choice;

    do{
        cout << "\nCustomer Menu\n" << endl;
        cout << "1. View Balance\n" << endl;
        cout << "2. Deposit\n" << endl;
        cout << "3. Withdraw\n" << endl;
        cout << "4. Exit\n" << endl;
        cout << "Enter choice: " << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Balance: " << c.balance << endl;
            break;
        case 2:
            cout << "Deposit coming next..." << endl;
            break;
        case 3:
            cout << "Withdraw coming next..." << endl;
            break;
        case 4:
            cout << "Exiting..." << endl;
        default:
            cout << "Invalid Option" << endl;
            break;
        }
    }while (choice != 4);
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