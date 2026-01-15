#pragma once
#include <iostream>
#include "ClsUser.h"
#include "ClsScreen.h"
#include "PrintAccount.h"
#include "/Users/dell/Desktop/libraries/ClsInputValidate.h"
using namespace std;
class ClsUpdateUser:protected ClsScreen
{
    enum En_UpdateMenuOptions
    {
        eFirstName = 1,
        eLastName = 2,
        eEmail = 3,
        ePhone = 4,
        ePassword = 5,
        ePermissions = 6,
        eAll = 7,
        eSaveAndExit = 8
    };
     static void DisplayUpdateMenu()
    {
        cout << "\n\t\t\t\t=========================================\n";
        cout << "\t\t\t\t         Update Client Menu            \n";
        cout << "\t\t\t\t=========================================\n";
        cout << "\t\t\t\t1. Update First Name\n";
        cout << "\t\t\t\t2. Update Last Name\n";
        cout << "\t\t\t\t3. Update Email\n";
        cout << "\t\t\t\t4. Update Phone Number\n";
        cout << "\t\t\t\t5. Update Password\n";
        cout << "\t\t\t\t6. Update Permissions\n";
        cout << "\t\t\t\t7. Update All Fields\n";
        cout << "\t\t\t\t8. Save and Exit\n";
        cout << "\t\t\t\t=========================================\n";
    }
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
    static void _performUserUpdate(ClsUser &user, int Choice)
    {
        switch (Choice)
        {
        case eFirstName:
            cout << "Enter First Name: ";
            user.SetFirstName(clsInputValidate::ReadString());
            break;
        case eLastName:
            cout << "Enter Last Name: ";
            user.SetLastName(clsInputValidate::ReadString());
            break;
        case eEmail:
            cout << "Enter Email: ";
            user.SetEmail(clsInputValidate::ReadString());
            break;
        case ePhone:
            cout << "Enter Phone Number: ";
            user.SetPhone(clsInputValidate::ReadString());
            break;
        case ePassword:
            cout << "Enter Password: ";
            user.SetPassword(clsInputValidate::ReadString());
            break;
        case ePermissions:
            user.SetPermissions(_ReadPermissionsToSet());
            break;
        case eAll:
            ReadUserData(user);
            break;
        case eSaveAndExit:
            break;
        }
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
        }
        return permissions;
    }




    
public:
static void UpdateUser()
    {
        DisplayScreenTitle("Update Client Screen");
        int count = 0;
       string Username="";
        while (count < 3)
        {
            cout << "Enter Account Number to update: ";
             Username= clsInputValidate::ReadString( );
            if (!ClsUser::IsFound(Username))
            {
                cout << "Account not found. Please try again.\n";
                count++;
            }
            else
            {
                ClsUser client = ClsUser::Find(Username);
                ClsPrintUsers::PrintUserCard(client);
                while (true)
                {
                    DisplayUpdateMenu();
                    int choice = clsInputValidate::ReadIntNumberBetween("Enter your choice: ", 1, 8);
                    if (choice == En_UpdateMenuOptions::eSaveAndExit)
                    {
                        break;
                    }
                    _performUserUpdate(client, choice);
                    cout << "Field updated successfully.\n";
                    ClsPrintUsers::PrintUserCard(client);
                }

                if (client.SaveToFile() == ClsUser::enSaveMode::SaveSucceeded)
                {
                    cout << "Account updated successfully.\n";
                    ClsPrintUsers::PrintUserCard(client);
                }
                else
                {
                    cout << "Failed to update account.\n";
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