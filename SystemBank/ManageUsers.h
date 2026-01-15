#pragma once
#include <string>
#include "ClsBankClient.h"
#include "/Users/dell/Desktop/libraries/ClsInputValidate.h"
#include "ClsScreen.h"
#include "showUsersList.h"
#include "AddUser.h"
#include "DeletUser.h"
#include "UpdateUser.h"
#include "FindUser.h"
using namespace std;
class CLsManageUsers : protected ClsScreen
{
    enum enManageUsersOptions
    {
        eListUsers = 1,
        eAddNewUser = 2,
        eDeleteUser = 3,
        eUpdateUser = 4,
        eFinduser = 5,
        eMainMenu = 6
    };
    static void _ManageUsersMenu()
    {
        cout << "\n\t\t\t\t=========================================\n";
        cout << "\t\t\t\t\tManage Users Menu Options\n";
        cout << "\t\t\t\t=========================================\n";
        cout << "\t\t\t\t\t[1] List Users.\n";
        cout << "\t\t\t\t\t[2] Add New User.\n";
        cout << "\t\t\t\t\t[3] Delete User.\n";
        cout << "\t\t\t\t\t[4] Update User.\n";
        cout << "\t\t\t\t\t[5] Find User.\n";
        cout << "\t\t\t\t\t[6] Main Menu.\n";
        cout << "\t\t\t\t=========================================\n";
    }

    static void _PerformManageUsersOption(enManageUsersOptions Option)
    {
        switch (Option)
        {
        case eListUsers:
            system("cls");
            ShowUsersList::UsersList();
            break;
        case eAddNewUser:
            system("cls");
            ClsAddUser::AddNewUser();
            break;
        case eDeleteUser:
            system("cls");
            ClsDeleteUser::DeleteUser();
            break;
        case eUpdateUser:
            system("cls");
            ClsUpdateUser::UpdateUser();
            break;
        case eFinduser:
            system("cls");
            ClsFindUser::ShowFindUserMenu();
            break;
        case eMainMenu:
            system("cls");
            break;
        default:
            break;
        }
    }

public:
    static void ShowManageUsersScreen()
    {
        if (!CheckAccessRights(ClsUser::enPermissions::pManageUsers))
        {
            DisplayScreenTitle("\033[31mYou Don't Have Permission to Manage Users\033[0m");
            return;
        }
        DisplayScreenTitle("\tManage Users Screen");
        bool exit = false;
        while (!exit)
        {
            _ManageUsersMenu();
            int Option = clsInputValidate::ReadIntNumberBetween("Choose what you want to do (1-6): ", 1, 6);
            _PerformManageUsersOption((enManageUsersOptions)Option);
            if (Option == eMainMenu)
            {
                exit = false;
                break;
            }
            cout << "press any key to continue...";
            system("pause");
        }
    }
};