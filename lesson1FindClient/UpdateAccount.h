#pragma once
#include <iostream>
#include "ClsBankClient.h"
#include "ClsScreen.h"
#include "PrintAccount.h"
#include "/Users/dell/Desktop/libraries/ClsInputValidate.h"
using namespace std;
class ClsUpdateAccount : protected ClsScreen
{
    enum En_UpdateMenuOptions
    {
        eFirstName = 1,
        eLastName = 2,
        eEmail = 3,
        ePhone = 4,
        ePincode = 5,
        eAccountBalance = 6,
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
        cout << "\t\t\t\t5. Update PinCode\n";
        cout << "\t\t\t\t6. Update Account Balance\n";
        cout << "\t\t\t\t7. Update All Fields\n";
        cout << "\t\t\t\t8. Save and Exit\n";
        cout << "\t\t\t\t=========================================\n";
    }
    static void ReadNewClientData(ClsBankClient &client)
    {
        cout << "Enter First Name: ";
        client.SetFirstName(clsInputValidate::ReadString());
        cout << "Enter Last Name: ";
        client.SetLastName(clsInputValidate::ReadString());
        cout << "Enter Email: ";
        client.SetEmail(clsInputValidate::ReadString());
        cout << "Enter Phone Number: ";
        client.SetPhone(clsInputValidate::ReadString());
        cout << "Enter PinCode: ";
        client.SetPincode(clsInputValidate::ReadString());
        client.SetAccountBalance(clsInputValidate::readnumber("Enter Account Balance: "));
    }
    static void PerformClientUpdate(ClsBankClient &client, int Choice)
    {
        switch (Choice)
        {
        case eFirstName:
            cout << "Enter First Name: ";
            client.SetFirstName(clsInputValidate::ReadString());
            break;
        case eLastName:
            cout << "Enter Last Name: ";
            client.SetLastName(clsInputValidate::ReadString());
            break;
        case eEmail:
            cout << "Enter Email: ";
            client.SetEmail(clsInputValidate::ReadString());
            break;
        case ePhone:
            cout << "Enter Phone Number: ";
            client.SetPhone(clsInputValidate::ReadString());
            break;
        case ePincode:
            cout << "Enter PinCode: ";
            client.SetPincode(clsInputValidate::ReadString());
            break;
        case eAccountBalance:
            client.SetAccountBalance(clsInputValidate::readnumber("Enter Account Balance: "));
            break;
        case eAll:
            ReadNewClientData(client);
            break;
        case eSaveAndExit:
            break;
        }
    }

public:
    static void UpdateAccount()
    {
        DisplayScreenTitle("Update Client Screen");
        int count = 0;
        int accNum = 0;
        while (count < 3)
        {
            accNum = clsInputValidate::readnumber("Enter Account Number to update: ");
            if (!ClsBankClient::IsFound(accNum))
            {
                cout << "Account not found. Please try again.\n";
                count++;
            }
            else
            {
                ClsBankClient client = ClsBankClient::Find(accNum);
                ClsPrintAccount::PrintAccountCard(client);
                while (true)
                {
                    DisplayUpdateMenu();
                    int choice = clsInputValidate::ReadIntNumberBetween("Enter your choice: ", 1, 8);
                    if (choice == En_UpdateMenuOptions::eSaveAndExit)
                    {
                        break;
                    }
                    PerformClientUpdate(client, choice);
                    cout << "Field updated successfully.\n";
                    ClsPrintAccount::PrintAccountCard(client);
                }

                if (client.SaveToFile() == ClsBankClient::enSaveMode::SaveSucceeded)
                {
                    cout << "Account updated successfully.\n";
                    ClsPrintAccount::PrintAccountCard(client);
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