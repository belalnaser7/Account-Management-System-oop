#pragma once
#include <iostream>
#include "ClsBankClient.h"
#include "ClsScreen.h"
#include "PrintAccount.h"
#include "/Users/dell/Desktop/libraries/ClsInputValidate.h"
#define Blue "\033[34m"
#define MAGENTA "\033[35m"
#define RESET "\033[0m"
#define RED "\033[31m"
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
        cout << MAGENTA << "\n\t\t\t\t=========================================\n"
             << RESET;
        cout << Blue << "\t\t\t\t         Update Client Menu            \n"
             << RESET;
        cout << MAGENTA << "\t\t\t\t=========================================\n"
             << RESET;
        cout << Blue << "\t\t\t\t[1]" << RESET << " Update First Name\n";
        cout << Blue << "\t\t\t\t[2]" << RESET << " Update Last Name\n";
        cout << Blue << "\t\t\t\t[3]" << RESET << " Update Email\n";
        cout << Blue << "\t\t\t\t[4]" << RESET << " Update Phone Number\n";
        cout << Blue << "\t\t\t\t[5]" << RESET << " Update Pincode\n";
        cout << Blue << "\t\t\t\t[6]" << RESET << " Update Account Balance\n";
        cout << Blue << "\t\t\t\t[7]" << RESET << " Update All Fields\n";
        cout << Blue << "\t\t\t\t[8]" << RESET << " Save and Exit\n";

        cout << MAGENTA << "\t\t\t\t=========================================\n"
             << RESET;
    }
    static void ReadNewClientData(ClsBankClient &client)
    {

        client.SetFirstName(clsInputValidate::ReadString("\033[36mEnter First Name: \033[0m"));
        client.SetLastName(clsInputValidate::ReadString("\033[36mEnter Last Name: \033[0m"));
        client.SetEmail(clsInputValidate::ReadString("\033[36mEnter Email: \033[0m"));
        client.SetPhone(clsInputValidate::ReadString("\033[36mEnter Phone Number: \033[0m"));
        client.SetPincode(clsInputValidate::ReadString("\033[36mEnter PinCode: \033[0m"));
        client.SetAccountBalance(clsInputValidate::readnumber("\033[36mEnter Account Balance: \033[0m"));
        cout << GREEN << "\nAll inputs recorded successfully!" << RESET << endl;
    }
    static void PerformClientUpdate(ClsBankClient &client, int Choice)
    {
        switch (Choice)
        {
        case eFirstName:
            client.SetFirstName(clsInputValidate::ReadString("\033[36mEnter First Name: \033[0m"));
            break;
        case eLastName:
            client.SetLastName(clsInputValidate::ReadString("\033[36mEnter Last Name: \033[0m"));
            break;
        case eEmail:
            client.SetEmail(clsInputValidate::ReadString("\033[36mEnter Email: \033[0m"));
            break;
        case ePhone:
            client.SetPhone(clsInputValidate::ReadString("\033[36mEnter Phone Number: \033[0m"));
            break;
        case ePincode:
            client.SetPincode(clsInputValidate::ReadString("\033[36mEnter PinCode: \033[0m"));
            break;
        case eAccountBalance:
            client.SetAccountBalance(clsInputValidate::readnumber("\033[36mEnter Account Balance: \033[0m"));
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
        if (!CheckAccessRights(ClsUser::enPermissions::pUpdateClient))
        {
            BlockScreenDisplay("\033[31mYou Don't Have Permission to Update Client\033[0m");
            return;
        }
        DisplayScreenTitle("Update Client Screen");
        int count = 0;
        int accNum = 0;
        while (count < 3)
        {
            accNum = clsInputValidate::readnumber("Enter Account Number to update: ");
            if (!ClsBankClient::IsFound(accNum))
            {
                cout << RED << "Account not found. Please try again.\n"
                     << RESET;
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
                    cout << GREEN << "Field updated successfully.\n"
                         << RESET;
                    ClsPrintAccount::PrintAccountCard(client);
                }

                if (client.SaveToFile() == ClsBankClient::enSaveMode::SaveSucceeded)
                {
                    cout << GREEN << "Account updated successfully.\n"
                         << RESET;
                    ClsPrintAccount::PrintAccountCard(client);
                }
                else
                {
                    cout << RED << "Failed to update account.\n"
                         << RESET;
                }
                break;
            }
        }
        if (count >= 3)
        {
            cout << RED << "You have exceeded the maximum number of attempts.\n"
                 << RESET;
        }
    }
};