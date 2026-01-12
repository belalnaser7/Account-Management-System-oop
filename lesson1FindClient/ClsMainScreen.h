#pragma once
#include <iostream>
#include "ClsScreen.h"
#include "ClsBankClient.h"
#include "showClientsList.h"
#include "FindAccountClient.h"
#include "AddNewClient.h"
#include "DeleteAccount.h"
#include "UpdateAccount.h"
#include "/Users/dell/Desktop/libraries/ClsInputValidate.h"
using namespace std;
class ClsMainScreen : protected ClsScreen
{
    enum En_MainMenuOptions
    {
        eFindClient = 1,
        eAddNewClient = 2,
        eDeleteClient = 3,
        eUpdateClient = 4,
        eAllClientsList = 5,
        eTransaction = 6,
        eManageUsers = 7,
        eExit = 8
    };
    static void ShowFindClient()
    {
        ClsFindAccountClient::ShowFindAccountClient();
    }
    static void ShowAddNewClient()
    {
        AddNewClient::AddNewAccount();
    }
    static void ShowDeleteClient()
    {
        ClsDeleteAccount::DeleteAccount();
    }
    static void ShowUpdateClient()
    {
        ClsUpdateAccount::UpdateAccount();
    }
    static void ShowClientsList()
    {
        ClsShowClientsList::ShowClientsList();
    }
    static void ShowTransaction()
    {
        cout << "Transaction Screen\n";
    }
    static void ShowManageUsers()
    {
        cout << "Manage Users Screen\n";
    }
    static bool Exit()
    {
        cout << "\n\t\t\t\tThank you for using our system. Goodbye!\n";
        return true;
    }
    static void PerformMainMenueOption(En_MainMenuOptions Option)
    {
        switch (Option)
        {
        case eFindClient:
            system("cls");
            ShowFindClient();
            break;
        case eAddNewClient:
            system("cls");
            ShowAddNewClient();
            break;
        case eDeleteClient:
            system("cls");
            ShowDeleteClient();
            break;
        case eUpdateClient:
            system("cls");
            ShowUpdateClient();
            break;
        case eAllClientsList:
            system("cls");
            ShowClientsList();
            break;
        case eTransaction:
            system("cls");
            ShowTransaction();
            break;
        case eManageUsers:
            system("cls");
            ShowManageUsers();
            break;
        case eExit:
            system("cls");
           cout << Exit();
            break;
        }
    }
public:
    static void ShowMainScreen()
    {  
        while (true)
        {
            system("cls");
        ClsScreen::DisplayScreenTitle("Main Screen");
            cout << "\n\t\t\t\t\t[1] Find Client.";
            cout << "\n\t\t\t\t\t[2] Add New Client.";
            cout << "\n\t\t\t\t\t[3] Delete Client.";
            cout << "\n\t\t\t\t\t[4] Update Client.";
            cout << "\n\t\t\t\t\t[5] Show Clients List.";
            cout << "\n\t\t\t\t\t[6] Transactions.";
            cout << "\n\t\t\t\t\t[7] Manage Users.";
            cout << "\n\t\t\t\t\t[8] Exit.";
            int Choice = clsInputValidate::ReadIntNumberBetween("\n\n\t\t\t\tChoose what do you want to do? [1-8]: ", 1, 8);
            PerformMainMenueOption((En_MainMenuOptions)Choice);
            cout << "" << "\n\tPress any key to go back to Main Menue...\n";
            system("pause");
        }
    }
};