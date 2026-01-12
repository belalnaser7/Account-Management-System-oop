#pragma once
#include <iostream>
#include "ClsBankClient.h"
using namespace std;
class ClsPrintAccount
{
public:
    static void PrintAccountCard(const ClsBankClient &client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << client.GetFirstName();
        cout << "\nLastName    : " << client.GetLastName();
        cout << "\nEmail       : " << client.GetEmail();
        cout << "\nPhone       : " << client.GetPhone();
        cout << "\nFull Name   : " << client.GetFullName();
        cout << "\nAcc. Number : " << client.GetAccountNumber();
        cout << "\nPinCode     : " << client.GetPincode();
        cout << "\nBalance     : " << client.GetAccountBalance();
        cout << "\n___________________\n";
    }
};