#pragma once
#include <iostream>
#include "ClsBankClient.h"
#include "ClsMainScreen.h"
#include <iomanip>
#include "ClsUser.h"
#include "Global.h"

using namespace std;
class ClsShowClientsList : protected ClsScreen
{
    static void PrintClientRecordLine(ClsBankClient Client)
    {
        cout << "| " << setw(15) << left << Client.GetAccountNumber();
        cout << "| " << setw(20) << left << Client.GetFullName();
        cout << "| " << setw(12) << left << Client.GetPhone();
        cout << "| " << setw(20) << left << Client.GetEmail();
        cout << "| " << setw(10) << left << Client.GetPincode();
        cout << "| " << setw(12) << left << Client.GetAccountBalance();
    }

public:
    static void ShowClientsList()
    {
       if(!CheckAccessRights(ClsUser::enPermissions::pListClients))
        {
              DisplayScreenTitle("\033[31mYou Don't Have Permission to List Clients\033[0m");
            return;
        }
        ClsScreen::DisplayScreenTitle("Show Clients List");
        vector<ClsBankClient> vClients = ClsBankClient::GetClientsList();
        cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n"
             << endl;
        cout << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Balance";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n"
             << endl;
        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else
            for (ClsBankClient Client : vClients)
            {
                PrintClientRecordLine(Client);
                cout << endl;
            }
        // cout << "\nTotal Balances = " << ClsBankClient::totalBalances() << endl;
        // cout << "Only "<<clsUtility::numbertotext(ClsBankClient::totalBalances())<<" Dollars";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n"
             << endl;
    }
};
