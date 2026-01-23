#pragma once
#include <iostream>
#include <string>
#include "ClsUser.h"
#include "ClsScreen.h"
#include "PrintAccount.h"
#include "/Users/dell/Desktop/libraries/ClsInputValidate.h"
using namespace std;
class ClsFindUser : protected ClsUser
{
    enum MenuOptions
    {
        FindByUser = 1,
        FindByPasswordAndUser = 2,
        BackToMain = 3
    };
    static void _FindUserMenu()
    {
        cout << "\n\t\t\t\t=========================================\n";
        cout << "\t\t\t\t\tFind User Menu Options\n";
        cout << "\t\t\t\t=========================================\n";
        cout << "\t\t\t\t\t[1] Find by User Name.\n";
        cout << "\t\t\t\t\t[2] Find by Password and User Name.\n";
        cout << "\t\t\t\t\t[3] Back to Main Menu.\n";
        cout << "\t\t\t\t=========================================\n";
    }
    static void FindByUserName()
    {
        int count = 0;
        string userName;
        while (count < 3)
        {
            userName = clsInputValidate::ReadString("Enter UserName to FindClient: ");
            if (ClsUser::IsFound(userName))
            {
                ClsUser user = ClsUser::Find(userName);
                ClsPrintUsers::PrintUserCard(user);
                return;
            }
            count++;
            cout << "User not found. Attempts left: " << (3 - count) << "\n";
        }
        cout << "You have exceeded the maximum number of attempts.\n";
    }
    static void FindByPasswordAndUserName()
    {
        int count = 0;
        string userName = "";
        int password = 0;
        while (count < 3)
        {
            userName = clsInputValidate::ReadString("Enter UserName to FindClient: ");
            password = clsInputValidate::readnumber("Enter Password to FindClient: ");
            if (ClsUser::IsFound(userName, password))
            {
                ClsUser user = ClsUser::Find(userName, password);
                ClsPrintUsers::PrintUserCard(user);
                return;
            }
            count++;
            cout << "User not found. Attempts left: " << (3 - count) << "\n";
        }
        cout << "You have exceeded the maximum number of attempts.\n";
    }
    static void _performUserUpdate(int choice)
    {
        switch (choice)
        {
        case FindByUser:
            system("cls");
            FindByUserName();
            break;
        case FindByPasswordAndUser:
            system("cls");
            FindByPasswordAndUserName();
            break;
        case BackToMain:
            system("cls");
            break;
        default:
            break;
        }
    }

public:
    static void ShowFindUserMenu()
    {
        int choice = 0;
        while (choice != BackToMain)
        {
            _FindUserMenu();
            choice = clsInputValidate::ReadIntNumberBetween("Enter your choice: ", 1, 3);
            _performUserUpdate(choice);
              cout << "" << "\n\tPress any key to go back to Main Menue...\n";
        system("pause");
        }
      
    }
};