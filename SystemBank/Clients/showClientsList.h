#pragma once
#include <iostream>
#include "ClsBankClient.h"
#include <iomanip>
#include "ClsUser.h"
#include "Global.h"

using namespace std;
class ClsShowClientsList : protected ClsScreen
{
    static void PrintClientRecordLine(ClsBankClient Client)
    {
        cout << "| "  << setw(10) << left << Client.GetAccountNumber();
        cout << "| "  <<setw(20) << left << Client.GetFullName();
        cout << "| "  << setw(12) << left << Client.GetPhone();
        cout << "| "  <<setw(25) << left << Client.GetEmail();
        cout << "| "  <<setw(10) << left << Client.GetPincode();
        cout << "| "  << setw(10) << left << Client.GetAccountBalance();
        cout <<MAGENTA<< "\n_______________________________________________________";
        cout << "_________________________________________\n"<<RESET;
        
    }

public:
    static void ShowClientsList()
    {
       if(!CheckAccessRights(ClsUser::enPermissions::pListClients))
        {
             BlockScreenDisplay("\033[31mYou Don't Have Permission to List Clients\033[0m");
            return;
        }
        ClsScreen::DisplayScreenTitle("Show Clients List");
        vector<ClsBankClient> vClients = ClsBankClient::GetClientsList();
        cout << "\n\n\t\t\t\t\tClient List ("<<Blue << vClients.size()<<RESET << ") Client(s)."<<endl;
        cout << "| " <<Blue<< left << setw(10) << "Acc"<<RESET;
        cout << "| " <<Blue << left << setw(20) << "Client Name"<<RESET;
        cout << "| " <<Blue<< left << setw(12) << "Phone"<<RESET;
        cout << "| " <<Blue<< left << setw(25) << "Email"<<RESET;
        cout << "| " <<Blue<< left << setw(10) << "Pin"<<RESET;
        cout << "| " <<Blue<< left << setw(10) << "Balance"<<RESET;
         cout <<MAGENTA<< "\n_______________________________________________________";
        cout << "_________________________________________\n"<<RESET;
        if (vClients.size() == 0)
            cout <<  "\t\t\t\tNo Clients Available In the System!";
        else
            for (ClsBankClient Client : vClients)
            {
                PrintClientRecordLine(Client);
                cout << endl;
            }
             
    }
};
