#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "/Users/dell/Desktop/libraries/Clsstring.h"
#include "ClsPerson.h"

using namespace std;

class ClsBankClient : public ClsPerson
{
private:
    // =========================
    // ENUMERATIONS
    // =========================
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

    // =========================
    // Member variables
    // =========================

    enMode _Mode;
    string _AccountNumber;
    string _Pincode;
    int _AccountBalance;
    bool MarkedForDelete = false;

    // Return an empty client object
    static ClsBankClient _GetEmptyClientObject()
    {
        return ClsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }
    // Deserialize a CSV line into a ClsBankClient object
    static ClsBankClient _deserializeAccount(const string &line)
    {
        vector<string> parts = ClsString::Split(line, ",");

        if (parts.size() != 7)
        {
            // cout << "Invalid line found: " << line << endl;
            return _GetEmptyClientObject();
        }

        float balance = 0;
        try
        {
            balance = stof(parts[enFields::FldAccountBalance]);
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
    // Serialize a ClsBankClient object into a CSV line
    static string _SerializeAccount(const ClsBankClient &client)
    {
        return client.GetFristName() + "," +
               client.GetLastName() + "," +
               client.GetEmail() + "," +
               client.GetPhone() + "," +
               client.GetAccountNumber() + "," +
               client.GetPincode() + "," +
               to_string(client.GetAccountBalance());
    }
    // Load all accounts from file
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
    // Save all accounts to file after update
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
    // Update the current client in the file
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
   // Add the current client to the file
    void _AddNewAccount()
    {
        vector<ClsBankClient> clients = _LoadAccountsFromFile();
        clients.push_back(*this);
        _SaveAccountsToFile(clients);
        _Mode = enMode::AddMode;
    }

    
public:
bool Delete(){
    vector<ClsBankClient> clients = _LoadAccountsFromFile();
    // for (auto &&i : clients)
    // {
    //     if (i.GetAccountNumber() == _AccountNumber)
    //     {
    //         i.MarkedForDelete = true;
    //         break;
    //     }
    // }
    // _SaveAccountsToFile(clients);
    // *this = _GetEmptyClientObject();
    // return true;
  
    for (auto it = clients.begin(); it != clients.end(); ++it)
    {
        if (it->GetAccountNumber() == GetAccountNumber())
        {
            clients.erase(it);
            _SaveAccountsToFile(clients);
            *this = _GetEmptyClientObject();
            return true; // Deletion successful
        }
    }
    return false; // Account not found

}
   
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

    // =========================
    // PROPERTY CHECKS
    // =========================
    bool IsEmpty() const
    {
        return (_Mode == EmptyMode);
    }

    // =========================
    // GETTERS & SETTERS
    // =========================
    string GetAccountNumber() const { return _AccountNumber; }

    void SetPincode(string Pin) { _Pincode = Pin; }
    string GetPincode() const { return _Pincode; }

    void SetAccountBalance(float Balance) { _AccountBalance = Balance; }
    float GetAccountBalance() const { return _AccountBalance; }

    // Find by AccountNumber
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
                to_string(Pincode) == Account.GetPincode() )
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

    // Account Saved to file after update
    enum enSaveMode
    {
        svFaildedAccountEmpty = 0,
        SaveSucceded = 1,
        svFaildedAccountExists = 2
    };
    enSaveMode SaveToFile()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
            return enSaveMode::svFaildedAccountEmpty;
        case enMode::UpdateMode:
            _update();
            return enSaveMode::SaveSucceded;
        case enMode::AddMode:
            if (ClsBankClient::IsFound(stoi(_AccountNumber)))
            {
                return enSaveMode::svFaildedAccountExists;
            }
            else
            {
                _AddNewAccount();
                _Mode = enMode::UpdateMode;
                return enSaveMode::SaveSucceded;
            }
        }
        return enSaveMode::svFaildedAccountEmpty;
    }

    static ClsBankClient AddObjectToFile(int accountNumber)
    {
        return ClsBankClient(enMode::AddMode, "", "", "", "", to_string(accountNumber), "", 0);
    }
    static vector<ClsBankClient> GetClientsList()
    {
        return _LoadAccountsFromFile();
    }
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
    static int NumberOfClientsCount()
    {
        vector<ClsBankClient> clients = _LoadAccountsFromFile();
        
        return static_cast<int>(clients.size());
    }

    // =========================
    // DISPLAY
    // =========================
    void Print() const
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << GetFristName();
        cout << "\nLastName    : " << GetLastName();
        cout << "\nEmail       : " << GetEmail();
        cout << "\nPhone       : " << GetPhone();
        cout << "\nFull Name   : " << GetFullName();
        cout << "\nAcc. Number : " << _AccountNumber;
        cout << "\nPinCode     : " << _Pincode;
        cout << "\nBalance     : " << _AccountBalance;
        cout << "\n___________________\n";
    }
};
