#pragma once
#include <iostream>
#include "ClsScreen.h"
#include "ClsUser.h"
#include <iomanip>
#include "/Users/dell/Desktop/libraries/ClsDate.h"
using namespace std;

class ShowLogsList : protected ClsScreen
{
    static void DisplayLogsListScreen(const ClsUser::stLoginRegisterRecord& user)
    {
        cout << "| " << left << setw(15) << user.Date;
        cout << "| " << left << setw(15) << user.Time;
        cout << "| " << left << setw(15) << user.UserName;
        cout << "| " << left << setw(10) << user.Password;
        cout << "| " << left << setw(12) << user.Permissions;
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }

public:
   static void ShowLogsListScreen()
    {
        if(!CheckAccessRights(ClsUser::enPermissions::pShowLogs)){
            DisplayScreenTitle("\033[31mYou Don't Have Permission to Show Logs\033[0m");
            return;
        }
       DisplayScreenTitle("Show Logs List");
        
        vector <ClsUser::stLoginRegisterRecord> Vlogs =ClsUser::GetLogsLists();
        cout << "\n\t\t\t\t\tLogs List (" << Vlogs.size() << ") User(s).";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << "| " << left << setw(15) << "Date";
        cout << "| " << left << setw(15) << "time";
        cout << "| " << left << setw(15) << "User Name";
        cout << "| " << left << setw(10) << "Password ";
        cout << "| " << left << setw(12) << "Permissions";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        if (Vlogs.size() == 0)
            cout << "\t\t\t\tNo Logs Available In the System!";
        else
        {
            for (auto record : Vlogs)
            {
                DisplayLogsListScreen(record);
            }
        }
    }
};