#pragma once
#include <iostream>
#include <string>
#include "ClsBankClient.h"
#include "ClsScreen.h"
#include "PrintAccount.h"
#include "/Users/dell/Desktop/libraries/ClsInputValidate.h"
using namespace std;
class ClsFindAccountClient : protected ClsScreen
{
    enum En_FindAccountMenuOptions
    {
        eFindByAccountNumber = 1,
        eFindByPinCode = 2
    };
    static void ShowFindByAccountNumber()
{
    int count = 0;
    int accNum;

    while (count < 3)
    {
        accNum = clsInputValidate::readnumber("Enter Account Number to FindClient: ");

        if (ClsBankClient::IsFound(accNum))
        {
            ClsBankClient client = ClsBankClient::Find(accNum);
            ClsPrintAccount::PrintAccountCard(client);
            return;
        }

        count++;
        cout << "Account not found. Attempts left: " << (3 - count) << "\n";
    }

    cout << "You have exceeded the maximum number of attempts.\n";
}

    static void ShowFindByPincodeAndAccountNumber()
    {
        int accNum = clsInputValidate::readnumber("Enter Account Number to FindClient: ");
        int pincode = clsInputValidate::readnumber("Enter PinCode to FindClient: ");
        while (!ClsBankClient::IsFound(accNum, pincode))
        {
            cout << "Account not found. Please try again.\n";
            accNum = clsInputValidate::readnumber("Enter Account Number to FindClient: ");
            pincode = clsInputValidate::readnumber("Enter PinCode to FindClient: ");
        }
        ClsBankClient client = ClsBankClient::Find(accNum, pincode);
        ClsPrintAccount::PrintAccountCard(client);
    }
    static void PerformFindAccountMenueOption(En_FindAccountMenuOptions Option)
    {
        switch (Option)
        {
        case eFindByAccountNumber:
            system("cls");
            ShowFindByAccountNumber();
            break;
        case eFindByPinCode:
            system("cls");
            ShowFindByPincodeAndAccountNumber();
            break;
        }
    }

public:
    static void ShowFindAccountClient()
    {
        ClsScreen::DisplayScreenTitle("Find Account Client");
        int choice = clsInputValidate::readnumber("1. Find by Account Number\n2. Find by PinCode\nEnter your choice: ");
        PerformFindAccountMenueOption((En_FindAccountMenuOptions)choice);
    }
};