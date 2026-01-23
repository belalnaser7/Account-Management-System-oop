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
#include "CurrenciesExchange.h"
#include "/Users/dell/Desktop/libraries/ClsInputValidate.h"
#include "Global.h"
#define MAGENTA "\033[35m"
#define RESET "\033[0m"

#define BLUE "\033[34m"

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
        enCurrencies = 9,
        eExit = 10
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
    static void ShowCurrencies()
    {
        ClsCurrenciesExchange::DisplayCurrenciesExchange();
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
        case enCurrencies:
            system("cls");
            ShowCurrencies();
            break;
        case eExit:
            system("cls");
            Exit();
            break;
        default:
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
            cout << BLUE << "\n\t\t\t\t\t[1]" << RESET << " Find Client.";
            cout << BLUE << "\n\t\t\t\t\t[2]" << RESET << " Add New Client.";
            cout << BLUE << "\n\t\t\t\t\t[3]" << RESET << " Delete Client.";
            cout << BLUE << "\n\t\t\t\t\t[4]" << RESET << " Update Client.";
            cout << BLUE << "\n\t\t\t\t\t[5]" << RESET << " All Clients List.";
            cout << BLUE << "\n\t\t\t\t\t[6]" << RESET << " Transaction.";
            cout << BLUE << "\n\t\t\t\t\t[7]" << RESET << " Manage Users.";
            cout << BLUE << "\n\t\t\t\t\t[8]" << RESET << " Show Logs List.";
            cout << BLUE << "\n\t\t\t\t\t[9]" << RESET << " Currencies Exchange.";
            cout << BLUE << "\n\t\t\t\t\t[10]" << RESET << " Exit.";
            int Choice = clsInputValidate::ReadIntNumberBetween("\n\n\t\t\t\tChoose what do you want to do? [1-10]: ", 1, 10);
            PerformMainMenueOption((En_MainMenuOptions)Choice);
            if (Choice == eExit)
            {
                break;
            }
            cout << MAGENTA << "\n\tPress any key to go back to Main Menue...\n"
                 << RESET;
            cin.ignore();
            cin.get();
        }
    }
};