#pragma once
#include <iostream>
#include "ClsUser.h"
#include "Global.h"
using namespace std;
class ClsScreen
{
protected:
    static void DisplayScreenTitle(string title)
    {

        cout << "\n\t\t\t\t=========================================\n";
        cout << "\t\t\t\t" << title << "\n";
        cout << "\t\t\t\t=========================================\n";
    }
    static bool CheckAccessRights( ClsUser::enPermissions requiredMode)
    {
        if(!CurrentUser.CheckAccessPermission(requiredMode))
        {
            return false;
        }
        return true;
    }
};
