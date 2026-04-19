#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

struct Customer{
    char acc[22];
    char pin[5];
    char name[32];
    double bal;
};

void createAccount(){
    Customer c;
    cout << "Create Customer Account\n";
    cout << "Enter Customer Name " << endl;
    cin >> c.name;
    cout << "Enter Account Number " << endl;
    cin >> c.acc;
    cout << "Enter TEMP Pin" << endl;
    cin >> c.pin;
    c.bal = 0;
    ofstream f("customer.dat", ios::binary | ios::app);

    f.write((char*)&c, sizeof(c));

    cout << "Account Created!\n";
    cout << "Welcome, " << c.name << ". Your account number is " << c.acc << endl;
}

int main(){
    createAccount();
}