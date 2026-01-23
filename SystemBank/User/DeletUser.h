#pragma once
#include <iostream>
#include "ClsUser.h"
#include "ClsScreen.h"
#include "PrintAccount.h"
#include "/Users/dell/Desktop/libraries/ClsInputValidate.h"
using namespace std;
class ClsDeleteUser:protected ClsScreen
{
    public:
     static void DeleteUser()
    {
        ClsScreen::DisplayScreenTitle("Delete User Screen");
        int count = 0;
        string UserName = "";
        while (count < 3)
        {
            cout << "Enter User Name to delete: ";
            UserName = clsInputValidate::ReadString();
            if (!ClsUser::IsFound(UserName))
            {
                cout << "User not found. Please try again.\n";
                count++;
            }
            else
            {
                ClsUser client = ClsUser::Find(UserName);
                ClsPrintUsers::PrintUserCard(client);
                cout << "Are you sure you want to delete this User? (Y/N): ";
                if (clsInputValidate::boolread())
                {
                    if (client.Delete())
                    {
                        cout << "User deleted successfully.\n";
                        ClsPrintUsers::PrintUserCard(client);
                        break;
                    }
                    else
                    {
                        cout << "Failed to delete User.\n";
                    }
                }
                else
                {
                    cout << "User deletion canceled.\n";
                }
                break;
            }
        }

        if (count >= 3)
        {
            cout << "You have exceeded the maximum number of attempts.\n";
        }
    }
    

};