#pragma once
#include <iostream>
#include "ClsScreen.h"
#include "ClsBankClient.h"
#include "showClientsList.h"
#include "FindAccountClient.h"
#include "AddNewClient.h"
#include "DeleteAccount.h"
#include "UpdateAccount.h"
#include "Transcations.h"
#include "ManageUsers.h"
#include "ShowLogsList.h"
#include "/Users/dell/Desktop/libraries/ClsInputValidate.h"
#include "Global.h"
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
        eShowLogsList = 8,
        eExit = 9
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
        ClsTranscations::ShowTransactions();
    }
    static void ShowManageUsers()
    {
        CLsManageUsers::ShowManageUsersScreen();
    }
    static void ShowLogsList()
    {
        ShowLogsList::ShowLogsListScreen();
    }
    static void Exit()
    {
        cout << "\n\t\t\t\tThank you for using our system. Goodbye!\n";
        CurrentUser = ClsUser::Find("", 0);
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
        case eShowLogsList:
            system("cls");
            ShowLogsList();
            break;
        case eExit:
            system("cls");
            Exit();
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
            cout << "\n\t\t\t\t\t[8] Show Logs List.";
            cout << "\n\t\t\t\t\t[9] Exit.";
            int Choice = clsInputValidate::ReadIntNumberBetween("\n\n\t\t\t\tChoose what do you want to do? [1-9]: ", 1, 9);
            PerformMainMenueOption((En_MainMenuOptions)Choice);
            if (Choice == eExit)
            {
                break;
            }

            cout << "" << "\n\tPress any key to go back to Main Menue...\n";
            system("pause");
        }
    }
};