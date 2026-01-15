#pragma once
#include <iostream>
#include "ClsBankClient.h"
#include "ClsScreen.h"
#include "PrintAccount.h"
#include "/Users/dell/Desktop/libraries/ClsInputValidate.h"
using namespace std;
class ClsDeleteAccount : protected ClsScreen
{
public:
    static void DeleteAccount()
    {
        if(!CheckAccessRights(ClsUser::enPermissions::pDeleteClient))
        {
              DisplayScreenTitle("\033[31mYou Don't Have Permission to Delete Client\033[0m");
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
                cout << "Account not found. Please try again.\n";
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
                        cout << "Account deleted successfully.\n";
                        ClsPrintAccount::PrintAccountCard(client);
                        break;
                    }
                    else
                    {
                        cout << "Failed to delete account.\n";
                    }
                }
                else
                {
                    cout << "Account deletion canceled.\n";
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