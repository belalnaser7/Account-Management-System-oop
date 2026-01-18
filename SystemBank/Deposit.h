#pragma once
#include <iostream>
#include "ClsBankClient.h"
#include "ClsScreen.h"
#include "PrintAccount.h"
#include "/Users/dell/Desktop/libraries/ClsInputValidate.h"
using namespace std;
class ClsDeposit : protected ClsScreen
{
public:
    static void DepositAmount()
    {
        ClsScreen::DisplayScreenTitle("Deposit Amount Screen");
        int count = 0;
        int accNum = 0;
        while (count < 3)
        {
            accNum = clsInputValidate::readnumber("Enter Account Number to Deposit: ");
            if (!ClsBankClient::IsFound(accNum))
            {
                cout << "Account not found. Please try again.\n";
                count++;
            }
            else
            {
                ClsBankClient client = ClsBankClient::Find(accNum);
                ClsPrintAccount::PrintAccountCard(client);
                float amount = clsInputValidate::readnumber("Enter amount to deposit: ");
                client.Deposit(amount);
                cout << "Deposit successful. New balance: " << client.GetAccountBalance() << "\n";
                ClsPrintAccount::PrintAccountCard(client);
            }
        }
        if (count >= 3)
        {
            cout << "You have exceeded the maximum number of attempts.\n";
        }
    }
};