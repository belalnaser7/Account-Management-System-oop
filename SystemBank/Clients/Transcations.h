#pragma once
#include <iostream>
#include "ClsBankClient.h"
#include "/Users/dell/Desktop/libraries/ClsInputValidate.h"
#include "Deposit.h"
#include "ClsScreen.h"
#include "Withdraw.h"
#include "TotalBalances.h"
#include "Transfer.h"
#include "ShowTransctionList.h"
using namespace std;
class ClsTranscations : protected ClsScreen
{
    enum enTransactionType
    {
        Deposit = 1,
        Withdraw = 2,
        Total = 3,
        Transfer=4,
        TransferList=5,
        MainMenu = 6
    };

    static void _TransactionMenu()
    {
        cout << "\n\t\t\t\t=========================================\n";
        cout << "\t\t\t\t\tTransaction Menu Options\n";
        cout << "\t\t\t\t=========================================\n";
        cout << "\t\t\t\t\t[1] Deposit Amount.\n";
        cout << "\t\t\t\t\t[2] Withdraw Amount.\n";
        cout << "\t\t\t\t\t[3] Total Balances.\n";
        cout << "\t\t\t\t\t[4] Transfer.\n";
        cout << "\t\t\t\t\t[5] Transfer List.\n";
        cout << "\t\t\t\t\t[6] Main Menu.\n";
        cout << "\t\t\t\t=========================================\n";
    }
    static void _PerformTransactionType(enTransactionType Type)
    {
        switch (Type)
        {
        case Deposit:
            system("cls");
            ClsDeposit::DepositAmount();
            break;
        case Withdraw:
            system("cls");
            ClsWithdraw::WithdrawAmount();
            break;
        case Total:
            system("cls");
            ClsTotalBalances::ShowTotalBalances();
            break;
        case Transfer:
            system("cls");
            ClsTransfer::TransferAmount();
            break;
        case TransferList:
            system("cls");
           ClsShowTransctionList::ShowTransctionList();
            break;
        case MainMenu:
            system("cls");
            break;
        default:
            break;
        }
    }
public:
    static void ShowTransactions()
    {
        if(!CheckAccessRights(ClsUser::enPermissions::pTranactions))
        {
             BlockScreenDisplay("\033[31mYou Don't Have Permission to Transactions\033[0m");
            return;
        }
        bool exit = false;
        while (!exit)
        {
            ClsScreen::DisplayScreenTitle("Transactions Screen");
            _TransactionMenu();
            int choice = clsInputValidate::ReadIntNumberBetween("Choose what you want to do (1-6): ", 1, 6);
            _PerformTransactionType((enTransactionType)choice);
            if (choice == enTransactionType::MainMenu)
            {
                exit = true;
                break;
            }
            cout << "\n\tPress any key to go back to Transactions Menu...\n";
            system("pause");
        }
    }
};