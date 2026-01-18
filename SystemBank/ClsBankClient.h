#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "/Users/dell/Desktop/libraries/Clsstring.h"
#include "/Users/dell/Desktop/libraries/ClsDate.h"
#include "ClsPerson.h"
#if 1
#define ENUMERATIONS 1
#define Member_Variables 1
#define Empty_Client_Object 1
#define Transfer_To_Line_And_Save_In_File 1
#define Serialize 1
#define Save_Accounts_To_File 1
#define Deserialize 1
#define Load_Accounts_From_File 1
#define Constructor 1
#define To_Update 1
#define To_Add 1
#define To_Delete 1
#define To_Find 1
#define Is_Found 1
#define To_SAVE 1
#define Total_Balances 1
#define Getters_Setters 1
#define Total_Number_Of_Clients 1
#define Get_Clients_List 1
#define Check_If_Object_Is_Empty 1
#endif
using namespace std;
class ClsBankClient : public ClsPerson
{
public:
    struct stTransaction
    {
        string Date;
        string Time;
        string S_AccountNumber;
        string D_AccountNumber;
        string Amount;
        string S_AccountBalance;
        string D_AccountBalance;
        string UserName;
    };
#if ENUMERATIONS
    enum enMode
    {
        EmptyMode = 0,
        UpdateMode = 1,
        AddMode = 2
    };
    enum enFields
    {
        FldFirstName = 0,
        FldLastName = 1,
        FldEmail = 2,
        FldPhone = 3,
        FldAccountNumber = 4,
        FldPincode = 5,
        FldAccountBalance = 6
    };
    enum enTransactionFields
    {
        TDate = 0,
        TTime = 1,
        TSAccountNumber = 2,
        TDAccountNumber = 3,
        TAmount = 4,
        TSAccountBalance = 5,
        TDAccountBalance = 6,
        TUserName = 7
    };
#endif
#if Member_Variables
    enMode _Mode;
    string _AccountNumber;
    string _Pincode;
    int _AccountBalance;
    bool MarkedForDelete = false;
#endif
#if Empty_Client_Object
    static ClsBankClient _GetEmptyClientObject()
    {
        return ClsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }
#endif
#if Transfer_To_Line_And_Save_In_File
#if Serialize
    static string _SerializeAccount(const ClsBankClient &client)
    {
        return client.GetFirstName() + "," +
               client.GetLastName() + "," +
               client.GetEmail() + "," +
               client.GetPhone() + "," +
               client.GetAccountNumber() + "," +
               client.GetPincode() + "," +
               to_string(client.GetAccountBalance());
    }
    string _SerializeTransfer(const ClsBankClient &client, int amount, string UserName, const string &dellem = "#//#")
    {
        return ClsDate::Gettodaydate() + dellem +
               ClsDate::Gettodaytime() + dellem +
               _AccountNumber + dellem +
               client.GetAccountNumber() + dellem +
               to_string(amount) + "$" + dellem +
               to_string(_AccountBalance) + "$" + dellem +
               to_string(client.GetAccountBalance()) + "$" + dellem +
               UserName;
    }
#endif
#if Save_Accounts_To_File
    static void _SaveAccountsToFile(const vector<ClsBankClient> &clients)
    {
        string line;
        ofstream fout("belal.txt", ios::trunc); // Open file in truncate mode to overwrite existing content
        for (const auto &client : clients)
        {
            if (client.MarkedForDelete)
                continue; // Skip clients marked for deletion
            line = _SerializeAccount(client);
            fout << line << endl;
        }
        fout.close();
    }
    void _SaveDataOFTransactionsToFile(ClsBankClient &DestinationClient, int amount, string UserName)
    {
        string line;
        ofstream fout("Transactions.txt", ios::app);
        line = _SerializeTransfer(DestinationClient, amount, UserName);
        fout << line << endl;
        fout.close();
    }
#endif
#endif
#if Deserialize
    static stTransaction _DeserializeTransaction(const string &line)
    {
        vector<string> parts = ClsString::Split(line, "#//#");
        if (parts.size() != 8)
        {
            return stTransaction();
        }
        stTransaction transaction;
        transaction.Date = parts[TDate];
        transaction.Time = parts[TTime];
        transaction.S_AccountNumber = parts[TSAccountNumber];
        transaction.D_AccountNumber = parts[TDAccountNumber];
        transaction.Amount = parts[TAmount];
        transaction.S_AccountBalance = parts[TSAccountBalance];
        transaction.D_AccountBalance = parts[TDAccountBalance];
        transaction.UserName = parts[TUserName];
        return transaction;
    }
    static ClsBankClient _deserializeAccount(const string &line)
    {
        vector<string> parts = ClsString::Split(line, ",");
        if (parts.size() != 7)
        {
            return _GetEmptyClientObject();
        }
        int balance = 0;
        try
        {
            balance = stoi(parts[enFields::FldAccountBalance]);
        }
        catch (...)
        {
            balance = -1;
        }
        // Construct object in UpdateMode (real client)
        return ClsBankClient(
            enMode::UpdateMode,
            parts[enFields::FldFirstName],     // FirstName
            parts[enFields::FldLastName],      // LastName
            parts[enFields::FldEmail],         // Email
            parts[enFields::FldPhone],         // Phone
            parts[enFields::FldAccountNumber], // AccountNumber
            parts[enFields::FldPincode],       // PinCode
            balance                            // AccountBalance
        );
    }
#endif
#if Load_Accounts_From_File
    static vector<stTransaction> _LoadTransactionsFromFile() 
    {
        vector<stTransaction> VTransaction;
        fstream fin("Transactions.txt");
        if (!fin.is_open())
            return VTransaction;
        string line;
        //stTransaction Transaction;
        while (getline(fin, line))
        {
            if (line.empty())
                continue;
                //Transaction = _DeserializeTransaction(line);
            VTransaction.push_back(_DeserializeTransaction(line));
        }
        fin.close();
        return VTransaction;
    }
    static vector<ClsBankClient> _LoadAccountsFromFile()
    {
        vector<ClsBankClient> Vclient;
        fstream fin("belal.txt");
        if (!fin.is_open())
            return Vclient;
        string line;
        while (getline(fin, line))
        {
            if (line.empty())
                continue;
            Vclient.push_back(_deserializeAccount(line));
        }
        fin.close();
        return Vclient;
    }
#endif
#if To_Update
    void _update()
    {
        vector<ClsBankClient> clients = _LoadAccountsFromFile();

        for (auto &client : clients)
        {
            if (client.GetAccountNumber() == GetAccountNumber())
            {
                client = *this;
                break;
            }
        }
        _SaveAccountsToFile(clients);
    }
#endif
#if To_Add
    void _AddNewAccount()
    {
        vector<ClsBankClient> clients = _LoadAccountsFromFile();
        clients.push_back(*this);
        _SaveAccountsToFile(clients);
        _Mode = enMode::AddMode;
    }
#endif
public:
#if Constructor
    ClsBankClient(enMode Mode,
                  string FirstName,
                  string LastName,
                  string Email,
                  string Phone,
                  string AccountNumber,
                  string PinCode,
                  float AccountBalance) : ClsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _Pincode = PinCode;
        _AccountBalance = AccountBalance;
    }
#endif
#if Getters_Setters
    string GetAccountNumber() const { return _AccountNumber; }

    void SetPincode(string Pin) { _Pincode = Pin; }
    string GetPincode() const { return _Pincode; }

    void SetAccountBalance(float Balance) { _AccountBalance = Balance; }
    int GetAccountBalance() const { return _AccountBalance; }
#endif
#if Check_If_Object_Is_Empty
    bool IsEmpty() const
    {
        return (_Mode == EmptyMode);
    }
#endif
#if To_Find
    static ClsBankClient Find(int AccountNumber)
    {
        vector<ClsBankClient> clients = _LoadAccountsFromFile();
        for (auto &Account : clients)
        {
            if (to_string(AccountNumber) == Account.GetAccountNumber())
                return Account;
        }
        return _GetEmptyClientObject();
    }
    // Find by AccountNumber + PinCode
    static ClsBankClient Find(int AccountNumber, const int &Pincode)
    {
        vector<ClsBankClient> clients = _LoadAccountsFromFile();
        for (auto &Account : clients)
        {
            if (to_string(AccountNumber) == Account.GetAccountNumber() &&
                to_string(Pincode) == Account.GetPincode())
                return Account;
        }
        return _GetEmptyClientObject();
    }
    // Check if account exists (by AccountNumber)
    static bool IsFound(int AccountNumber)
    {
        ClsBankClient Account = Find(AccountNumber);
        return !Account.IsEmpty();
    }
    // Check if account exists (by AccountNumber + PinCode)
    static bool IsFound(int AccountNumber, const int &Pincode)
    {
        ClsBankClient Account = Find(AccountNumber, Pincode);
        return !Account.IsEmpty();
    }
#endif
#if ENUMERATIONS
    enum enSaveMode
    {
        svFaildedAccountEmpty = 0,
        SaveSucceeded = 1,
        svFaildedAccountExists = 2
    };
#endif
#if To_SAVE
    enSaveMode SaveToFile()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
            return enSaveMode::svFaildedAccountEmpty;
        case enMode::UpdateMode:
            _update();
            return enSaveMode::SaveSucceeded;
        case enMode::AddMode:
            if (ClsBankClient::IsFound(stoi(_AccountNumber)))
            {
                return enSaveMode::svFaildedAccountExists;
            }
            else
            {
                _AddNewAccount();
                _Mode = enMode::UpdateMode;
                return enSaveMode::SaveSucceeded;
            }
        }
        return enSaveMode::svFaildedAccountEmpty;
    }
#endif
#if To_Add
    static ClsBankClient AddObjectToFile(int accountNumber)
    {
        return ClsBankClient(enMode::AddMode, "", "", "", "", to_string(accountNumber), "", 0);
    }
#endif
#if Get_Clients_List
    static vector<ClsBankClient> GetClientsList()
    {
        return _LoadAccountsFromFile();
    }
#endif
#if To_Delete
    bool Delete()
    {
        vector<ClsBankClient> clients = _LoadAccountsFromFile();
#if 0 // this is method using MarkedForDelete
            for (auto &&i : clients)
            {
                if (i.GetAccountNumber() == _AccountNumber)
                {
                    i.MarkedForDelete = true;
                    break;
                }
            }
            _SaveAccountsToFile(clients);
            *this = _GetEmptyClientObject();
            return true;
#else // this is method using iterator
        for (auto it = clients.begin(); it != clients.end(); ++it)
        {
            if (it->GetAccountNumber() == GetAccountNumber())
            {
                clients.erase(it);
                _SaveAccountsToFile(clients);
                *this = _GetEmptyClientObject();
                return true;
            }
        }
        return false;
#endif
    }
#endif
#if Total_Balances
    static int totalBalances()
    {
        vector<ClsBankClient> clients = _LoadAccountsFromFile();
        int total = 0;
        for (const auto &client : clients)
        {
            total += client.GetAccountBalance();
        }
        return total;
    }
#endif
#if Total_Number_Of_Clients

    static int NumberOfClientsCount()
    {
        vector<ClsBankClient> clients = _LoadAccountsFromFile();

        return static_cast<int>(clients.size());
    }

#endif
    void Deposit(int amount)
    {
        _AccountBalance += amount;
        _update();
    }
    void Withdraw(int amount)
    {
        _AccountBalance -= amount;
        _update();
    }
 static vector<stTransaction> DesplayTransactions() { return _LoadTransactionsFromFile(); }
    bool Transfer(int amount, ClsBankClient &DestinationClient, string UserName)
    {
        if (amount <= _AccountBalance)
        {
            Withdraw(amount);
            DestinationClient.Deposit(amount);
            _SaveDataOFTransactionsToFile(DestinationClient, amount, UserName);
            return true;
        }
        return false;
    }
};
