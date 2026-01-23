#pragma once
#include <iostream>
#include "ClsScreen.h"
#include "ClsBankClient.h"
#include "PrintAccount.h"
#include <iomanip>
#include "/Users/dell/Desktop/libraries/ClsInputValidate.h"
using namespace std;
class ClsShowTransctionList : protected ClsScreen
{
    static void DisplayTransctionList(const ClsBankClient::stTransaction &Transction)
    {
        cout << "|" << left << setw(12) << Transction.Date;
        cout << "|" << left << setw(12) << Transction.Time;
        cout << "|" << left << setw(12) << Transction.S_AccountNumber;
        cout << "|" << left << setw(12) << Transction.D_AccountNumber;
        cout << "|" << left << setw(12) << Transction.Amount;
        cout << "|" << left << setw(12) << Transction.S_AccountBalance;
        cout << "|" << left << setw(12) << Transction.D_AccountBalance;
        cout << "|" << left << setw(12) << Transction.UserName;
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n";
    }

public:
    static void ShowTransctionList()
    {
        DisplayScreenTitle("Show Transction List");
        vector<ClsBankClient::stTransaction> TransctionList = ClsBankClient::DesplayTransactions();
        cout << "\n\t\t\t\t\tTransction List (" << TransctionList.size() << ") User(s).";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n";
        cout << "| " << left << setw(12) << "Date";
        cout << "| " << left << setw(12) << "Time";
        cout << "| " << left << setw(12) << "S_Acc";
        cout << "| " << left << setw(12) << "D_Acc";
        cout << "| " << left << setw(12) << "Amount";
        cout << "| " << left << setw(12) << "S_Balance";
        cout << "| " << left << setw(12) << "D_Balance";
        cout << "| " << left << setw(12) << "UserName";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n";
        if (TransctionList.size() == 0)
        {
            cout << "\t\t\t\tNo Transction Available In the System!";
        }
        else
        {
            for (auto &i : TransctionList)
            {
                DisplayTransctionList(i);
            }
        }
    }
};