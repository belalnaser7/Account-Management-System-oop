#pragma once
#include <iostream>
#include "ClsBankClient.h"
#include "ClsScreen.h"
#include "PrintAccount.h"
#include "/Users/dell/Desktop/libraries/ClsInputValidate.h"
#define RED "\033[31m"
#define RESET "\033[0m"
#define GREEN "\033[32m"
#define Cryan "\033[36m"
using namespace std;
class ClsDeleteAccount : protected ClsScreen
{
public:
    static void DeleteAccount()
    {
        if(!CheckAccessRights(ClsUser::enPermissions::pDeleteClient))
        {
              BlockScreenDisplay("\033[31mYou Don't Have Permission to Delete Client\033[0m");
            return;
        }
        ClsScreen::DisplayScreenTitle("Delete Client Screen");
        int count = 0;
        int accNum = 0;
        while (count < 3)
        {
            accNum = clsInputValidate::readnumber("Enter Account Number to delete: ");
            if (!ClsBankClient::IsFound(accNum))
            {
                cout <<RED<< "Account not found. Please try again.\n"<<RESET;
                count++;
            }
            else
            {
                ClsBankClient client = ClsBankClient::Find(accNum);
                ClsPrintAccount::PrintAccountCard(client);
                cout << "Are you sure you want to delete this account? (Y/N): ";
                char confirmation = 'N';
                cin >> confirmation;
                if (toupper(confirmation) == 'Y')
                {
                    if (client.Delete())
                    {
                        cout <<GREEN<< "Account deleted successfully.\n"<<RESET;
                        ClsPrintAccount::PrintAccountCard(client);
                        break;
                    }
                    else
                    {
                        cout <<RED<< "Failed to delete account.\n"<<RESET;
                    }
                }
                else
                {
                    cout <<Cryan<< "Account deletion canceled.\n"<<RESET;
                }
                break;
            }
        }

        if (count >= 3)
        {
            cout <<RED<< "You have exceeded the maximum number of attempts.\n"<<RESET;
        }
    }
};