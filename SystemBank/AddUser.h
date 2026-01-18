#pragma once
#include <string>
#include "ClsUser.h"
#include "/Users/dell/Desktop/libraries/ClsInputValidate.h"
#include "ClsScreen.h"
#include "PrintAccount.h"
using namespace std;
class ClsAddUser : protected ClsScreen
{
    static void ReadUserData(ClsUser &user)
    {
        cout << "Enter First Name: ";
        user.SetFirstName(clsInputValidate::ReadString());
        cout << "Enter Last Name: ";
        user.SetLastName(clsInputValidate::ReadString());
        cout << "Enter Email: ";
        user.SetEmail(clsInputValidate::ReadString());
        cout << "Enter Phone: ";
        user.SetPhone(clsInputValidate::ReadString());
        cout << "Enter Password: ";
        user.SetPassword(clsInputValidate::ReadString());
        user.SetPermissions(_ReadPermissionsToSet());
    }

    static int _ReadPermissionsToSet()
    {
        int permissions = 0;
        cout << "Do you want to give all permissions? \n";
        if (clsInputValidate::boolread())
        {
            return permissions = ClsUser::enPermissions::pAll;
        }
        else
        {
            cout << "Do you want to give access to Premissions of : \n";
            cout << "Show List of Clients \n";
            if (clsInputValidate::boolread())
            {
                permissions |= ClsUser::enPermissions::pListClients;
            }
            cout << "Add New Client \n";
            if (clsInputValidate::boolread())
            {
                permissions |= 2;
            }
            cout << "Delete Client \n";
            if (clsInputValidate::boolread())
            {
                permissions |= 4;
            }
            cout << "Update Client \n";
            if (clsInputValidate::boolread())
            {
                permissions |= 8;
            }
            cout << "Find Client \n";
            if (clsInputValidate::boolread())
            {
                permissions |= 16;
            }
            cout << "Transaction Account \n";
            if (clsInputValidate::boolread())
            {
                permissions |= 32;
            }
            cout << "Manage Users \n";
            if (clsInputValidate::boolread())
            {
                permissions |= 64;
            }
            cout << "Show Logs List \n";
            if (clsInputValidate::boolread())
            {
                permissions |= 128;
            }
        }
        return permissions;
    }

public:
    static void AddNewUser()
    {
        ClsScreen::DisplayScreenTitle("Add New User Screen");
        int count = 0;
        string UserName = "";
        while (count < 3)
        {
            cout << "Enter User Name: ";
            UserName = clsInputValidate::ReadString();
            if (ClsUser::IsFound(UserName))
            {
                cout << "User already exists. Please try again.\n";
                count++;
            }
            else
            {
                ClsUser user = ClsUser::AddObjectToFile(UserName);
                ReadUserData(user);
                switch (user.SaveToFile())
                {
                case ClsUser::enSaveMode::SaveSucceeded:
                    cout << "User added successfully.\n";
                    ClsPrintUsers::PrintUserCard(user);
                    break;
                case ClsUser::enSaveMode::svFaildedAccountExists:
                    cout << "User already exists. Please try again.\n";
                    ClsPrintUsers::PrintUserCard(user);
                    break;
                case ClsUser::enSaveMode::svFaildedAccountEmpty:
                    cout << "Failed to add user. User data is empty.\n";
                    break;
                default:
                    break;
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