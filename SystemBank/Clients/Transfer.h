#pragma once
#include <iostream>
#include "ClsBankClient.h"
#include "ClsScreen.h"
#include "PrintAccount.h"
#include "/Users/dell/Desktop/libraries/ClsInputValidate.h"
#include "Global.h"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"
#define YELLOW "\033[33m"

using namespace std;
class ClsTransfer : protected ClsScreen
{
    static int _ReadAccountNumber(int &count)
    {
        int AccountNumber;
        count = 0;
        while (count < 3)
        {
            AccountNumber = clsInputValidate::readnumber("Enter Account Number to Transfer From: ");
            if (!ClsBankClient::IsFound(AccountNumber))
            {
                cout << RED << "\nAccount number is not found, choose another one: " << RESET << endl;
                count++;
            }
            else
            {
                count = 0;
                return AccountNumber;
            }
        }
        return 0;
    }
    static int _ReadAmount(ClsBankClient &client, int &count)
    {
        count = 0;
        while (count < 3)
        {
            int amount = clsInputValidate::readnumber("Enter amount to transfer: ");
            if (amount > client.GetAccountBalance())
            {
                cout << RED << "Insufficient balance. Current balance: " << client.GetAccountBalance() << RESET << "\n";
                count++;
            }
            else
            {
                count = 0;
                return amount;
            }
        }
        return 0;
    }
public:
    static void TransferAmount()
    {
        DisplayScreenTitle("Transfer Screen");
        int count = 0;
        int AccNum1 = 0;
        int AccNum2 = 0;
        int amount = 0;
        AccNum1 = _ReadAccountNumber(count);
        if (count >= 3)
        {
            cout << RED << "You have exceeded the maximum number of attempts." << RESET << endl;
            return;
        }
        ClsBankClient client1 = ClsBankClient::Find(AccNum1);
        ClsPrintTransaction::PrintTransactionCard(client1);
        AccNum2 = _ReadAccountNumber(count);
        if (count >= 3)
        {
            cout << RED << "You have exceeded the maximum number of attempts." << RESET << endl;
            return;
        }
        if (AccNum1 == AccNum2)
        {
            cout << RED << "You cannot transfer to the same account." << RESET << endl;
            return;
        }
        ClsBankClient client2 = ClsBankClient::Find(AccNum2);
        ClsPrintTransaction::PrintTransactionCard(client2);
        amount = _ReadAmount(client1, count);
        if (count >= 3)
        {
            cout << RED << "You have exceeded the maximum number of attempts." << RESET << endl;
            return;
        }
        cout << "Transfer amount: " << amount << endl;
        cout << "From: " << client1.GetFullName() << " To: " << client2.GetFullName() << endl;
        cout << YELLOW << "Are you sure you want to transfer this amount? (Y/N)" << RESET << endl;
        if (clsInputValidate::boolread())
        {
            if (client1.Transfer(amount, client2,CurrentUser.GetUserName()))
            {
                cout << GREEN << "Transfer successful" << RESET << endl;
            }
            else
            {
                cout << RED << "Transfer failed" << RESET << endl;
            }
        }
        else
        {
            cout << RED << "Transfer canceled" << RESET << endl;
        }
    }
};
