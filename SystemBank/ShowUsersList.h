#pragma once
#include <iostream>
#include "ClsScreen.h"
#include "ClsUser.h"
#include <iomanip>
using namespace std;

class ShowUsersList : protected ClsScreen
{
    static void DisplayUser(ClsUser user)
    {
        cout << "| " << left << setw(15) << user.GetUserName();
        cout << "| " << left << setw(20) << user.GetFullName();
        cout << "| " << left << setw(12) << user.GetPhone();
        cout << "| " << left << setw(20) << user.GetEmail();
        cout << "| " << left << setw(10) << user.GetPassword();
        cout << "| " << left << setw(12) << user.GetPermissions();
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n";
    }

public:
    static void UsersList()
    {
        ClsScreen::DisplayScreenTitle("Show Users List");
        vector <ClsUser> vUsers = ClsUser::GetUsersLists();
        cout << "\n\t\t\t\t\tUser List (" << vUsers.size() << ") User(s).";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << "| " << left << setw(15) << "User Name";
        cout << "| " << left << setw(20) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Password ";
        cout << "| " << left << setw(12) << "Permissions";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        if (vUsers.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else
        {
            for (ClsUser user : vUsers)
            {
                DisplayUser(user);
                cout << endl;
            }
        }
    }
};