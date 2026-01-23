#pragma once
#include <iostream>
#include "ClsUser.h"
#include "Global.h"
#include "/Users/dell/Desktop/libraries/ClsDate.h"
#include <ctime>
#define Blue "\033[34m"
#define MAGENTA "\033[35m"
#define RESET "\033[0m"
using namespace std;
class ClsScreen
{
protected:
    static void DisplayScreenTitle(string title)
    {

        cout << MAGENTA << "\n\t\t\t\t=========================================\n"
             << RESET;
        cout << Blue << "\t\t\t\t\t\t" << title << RESET;
        cout << MAGENTA << "\n\t\t\t\t=========================================\n"
             << RESET;
        cout << Blue << "\t\t\t\t" << MAGENTA << "Logged in as: " << RESET << CurrentUser.GetFullName() << MAGENTA << " User Name: " << RESET << CurrentUser.GetUserName() << "\n"
             << RESET;
        cout << Blue << "\t\t\t\t" << ClsDate::Gettodaydate() << "\n"
             << RESET;
    }
    static void BlockScreenDisplay(string title)
    {

        cout << MAGENTA << "\n\t\t\t\t=========================================\n"
             << RESET;
        cout << Blue << "\t\t\t\t" << title << RESET;
        cout << MAGENTA << "\n\t\t\t\t=========================================\n"
             << RESET;
        cout << Blue << "\t\t\t\t" << MAGENTA << "Logged in as: " << RESET << CurrentUser.GetFullName() << MAGENTA << " User Name: " << RESET << CurrentUser.GetUserName() << "\n"
             << RESET;
        cout << Blue << "\t\t\t\t" << ClsDate::Gettodaydate() << "\n"
             << RESET;
    }
    static bool CheckAccessRights(ClsUser::enPermissions requiredMode)
    {
        if (!CurrentUser.CheckAccessPermission(requiredMode))
        {
            return false;
        }
        return true;
    }
};
