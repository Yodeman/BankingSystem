#include <iostream>
#include <fstream>
#include <map>
using namespace std;
#define MIN_BALANCE 0

//class insufficientFunds{};

class Account{
private:
    int accountNumber;
    string firstName;
    string lastName;
    string e_mail;
    string phoneNumber;
    float balance;
    static int nextAccountNumber;
public:
    Account(){}
    Account(string fname, string lname, float balance, string mail, string phone){
        nextAccountNumber++;
        accountNumber = nextAccountNumber;
        firstName = fname;
        lastName = lname;
        e_mail = mail;
        phoneNumber = phone;
        if (balance < MIN_BALANCE)
            balance = MIN_BALANCE;
        else
            this->balance = balance;
    }
    long getAccNo() { return accountNumber; }
    string getFirstName() { return firstName; }
    string getLastName() { return lastName; }
    string getMail() { return e_mail; }
    string getPhoneNo() { return phoneNumber; }
    float getBalance() { return balance; }
    static void changeAccNoFormat(int newFormat) { nextAccountNumber = newFormat; }

    void deposit(float amount){
        balance += amount;
    }

    void withdraw(float amount){
        if ((balance-amount) < MIN_BALANCE ){
            cout << "Insufficient fund...\n\n";
        }
        else
            balance -= amount;
    }

    static void setLastAccountNumber(int accNo){
        //accountNumber = accNo;
        nextAccountNumber = accNo;
    }
    static int getLastAccountNumber(){ return nextAccountNumber; }
    friend ofstream &operator<<(ofstream &stream, Account &acc);
    friend ifstream &operator>>(ifstream &stream, Account &acc);
    friend ostream &operator<<(ostream &stream, Account &acc);
};

int Account::nextAccountNumber = 0214;

ofstream &operator<<(ofstream &stream, Account &acc){
    stream << acc.accountNumber << endl;
    stream << acc.firstName << endl;
    stream << acc.lastName << endl;
    stream << acc.e_mail << endl;
    stream << acc.phoneNumber << endl;
    stream << acc.balance << endl;

    return stream;
}

ifstream &operator>>(ifstream &stream, Account &acc){
    stream >> acc.accountNumber;
    stream >> acc.firstName;
    stream >> acc.lastName;
    stream >> acc.e_mail;
    stream >> acc.phoneNumber;
    stream >> acc.balance;

    return stream;
}

ostream &operator<<(ostream &stream, Account &acc){
    stream << "Name: " << acc.getLastName();
    stream << " ";
    stream << acc.getFirstName();
    stream << endl;
    stream << "Account Number: " << acc.getAccNo() << endl;
    stream << "E-mail: " << acc.getMail() << endl;
    stream << "Phone Number: " << acc.getPhoneNo() << endl;
    stream << "Balance: #" << acc.getBalance() << endl;
    stream << "\n";

    return stream;
}

class Bank{
private:
    map<int, Account> accounts;
public:
    Bank(){
        Account account;
        ifstream infile("C:\\Users\\USER\\Desktop\\my_c++_files\\C++\\BankingSystem\\BankData");
        if (!infile){
            cout << "File does not exists..."<< endl;
            return;
        }
        while(!infile.eof()){
            infile>>account;
            accounts.insert(pair<int, Account>(account.getAccNo(), account));
        }
        Account::setLastAccountNumber(account.getAccNo());
        infile.close();
    }
    Account openAccount(string fname, string lname, float balance, string mail, string phone){
        ofstream outfile("C:\\Users\\USER\\Desktop\\my_c++_files\\C++\\BankingSystem\\BankData", ios::trunc);
        Account account(fname, lname, balance, mail, phone);
        accounts.insert(pair<int, Account>(account.getAccNo(), account));
        map<int, Account>::iterator itr;
        for(itr=accounts.begin();itr!=accounts.end();itr++){
            outfile<<itr->second;
        }
        cout << "\nYour account has been successfully created...\n" << endl;
        outfile.close();
        return account;
    }
    Account BalanceEnquiry (int accNo){
        map<int, Account>::iterator itr=accounts.find(accNo);
        return itr->second;
    }
    Account Deposit(int accNo, float amount){
        map<int, Account>::iterator itr=accounts.find(accNo);
        itr->second.deposit(amount);
        return itr->second;
    }
    Account Withdraw(int accNo, float amount){
        map<int, Account>::iterator itr=accounts.find(accNo);
        itr->second.withdraw(amount);
        return itr->second;
    }
    void closeAccount(int accNo){
        map<int, Account>::iterator itr=accounts.find(accNo);
        cout << "Account " << itr->second.getAccNo() << "deleted.\n";
        accounts.erase(accNo);
    }
    void ShowAllAcounts(){
        map<int, Account>::iterator itr;
        for (itr=accounts.begin();itr!=accounts.end();itr++){
            cout << "Account " << itr->first << "\n" << itr->second << endl;
        }
    }
    void fetchAccInfo(int accNo){
        map<int, Account>::iterator itr=accounts.find(accNo);
        cout << "Account " << itr->first << "\n" << itr->second <<endl;
    }
    void changeAccNoFormat(int newFormat){
        Account::changeAccNoFormat(newFormat);
        Account::setLastAccountNumber(newFormat);
    }
    ~Bank(){
        ofstream outfile("C:\\Users\\USER\\Desktop\\my_c++_files\\C++\\BankingSystem\\BankData", ios::trunc);
        map<int, Account>::iterator itr;
        for (itr=accounts.begin();itr!=accounts.end();itr++){
            outfile<<itr->second;
        }
        outfile.close();
    }
};

int main(){
    Bank b;
    Account acc;
    int option, mode;
    string go, fname, lname, e_mail;
    string phone_number;
    int accNo, newAccFormat;
    float balance, amount;

    cout << "***Banking System***\n\n";
    cout << "\t1. Customer.\n";
    cout << "\t2. Bank Staff.\n";
    cout << "Enter option: ";
    cin >> mode;

   do{
        switch(mode){
            case 1:
                cout << "\tSelect one option below\n";
                cout << "\t1. Open an Account\n";
                cout << "\t2. Balance Inquiry\n";
                cout << "\t3. Deposit\n";
                cout << "\t4. Withdrawal\n";
                cout << "\t5. Quit\n";
                cout << "Enter option: ";
                cin >> option;
                //break;

                switch(option){
                    case 1:
                        cout << "Enter your first name: ";
                        cin >> fname;
                        cout << "Enter your last name: ";
                        cin >> lname;
                        cout << "Enter your e-mail: ";
                        cin >> e_mail;
                        cout << "Enter phone number: ";
                        cin >> phone_number;
                        cout << "Initial deposit: ";
                        cin >> balance;
                        cout << "creating account...\n";
                        acc = b.openAccount(fname, lname, balance, e_mail, phone_number);
                        cout << acc;
                        cout << "Want to perform another operation?(yes/no) ";
                        cin >> go;
                        break;
                    case 2:
                        cout << "Enter account number: ";
                        cin >> accNo;
                        cout << "Fetching account info...\n\n";
                        acc = b.BalanceEnquiry(accNo);
                        cout << acc;
                        cout << "Want to perform another operation?(yes/no) ";
                        cin >> go;
                        break;
                    case 3:
                        cout << "Enter account number: ";
                        cin >> accNo;
                        cout << "Enter amount: ";
                        cin >> amount;
                        cout << "Depositing...\n";
                        acc = b.Deposit(accNo, amount);
                        cout << "Amount " << amount << " deposited." << endl;
                        cout << acc;
                        cout << "Want to perform another operation?(yes/no) ";
                        cin >> go;
                        break;
                    case 4:
                        cout << "Enter account number: ";
                        cin >> accNo;
                        cout << "Enter amount: ";
                        cin >> amount;
                        cout << "Wait...\n";
                        acc = b.Withdraw(accNo, amount);
                        cout << "Amount " << amount << " withdrawn" << endl;
                        cout << acc;
                        cout << "\nWant to perform another operation?(yes/no) ";
                        cin >> go;
                        break;
                    case 5:
                        break;
                    default:
                        cout << "\nEnter correct option...";

                }
                break;
            case 2:
                cout << "\tSelect one option below\n";
                cout << "\t1. Close an Account.\n";
                cout << "\t2. Show All Accounts.\n";
                cout << "\t3. Get account info.\n";
                cout << "\t4. Reset account number\n";
                cout << "\t5. Quit\n";
                cout << "Enter option: ";
                cin >> option;
                //break;
                switch(option){
                    case 1:
                        cout << "Enter account number: ";
                        cin >> accNo;
                        cout << "deleting account...\n";
                        b.closeAccount(accNo);
                        cout << "Account closed.\n" << endl;
                        cout << "Want to perform another operation?(yes/no) ";
                        cin >> go;
                        break;
                    case 2:
                        cout << "Fetching all account...\n\n";
                        b.ShowAllAcounts();
                        cout << "Want to perform another operation?(yes/no) ";
                        cin >> go;
                        break;
                    case 3:
                        cout << "Enter account number: ";
                        cin >> accNo;
                        b.fetchAccInfo(accNo);
                        cout << "Want to perform another operation?(yes/no) ";
                        cin >> go;
                        break;
                    case 4:
                        cout << "Enter new account number format:";
                        cin >> newAccFormat;
                        b.changeAccNoFormat(newAccFormat);
                        cout << "Account number format changed.\n\n";
                        cout << "Want to perform another operation?(yes/no) ";
                        cin >> go;
                        break;
                    case 5:
                        break;
                    default:
                        cout << "Enter correct option...";
                }
                break;
            default:
            cout << "\nEnter correct option...";
        }
    }while(option!=5 && go == "yes");

    return 0;
}
