#pragma once
#include <iostream>
#include "ClsBankClient.h"
#include "ClsUser.h"
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

class ClsPrintUsers
{
public:
    static void PrintUserCard(const ClsUser &User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.GetFirstName();
        cout << "\nLastName    : " << User.GetLastName();
        cout << "\nEmail       : " << User.GetEmail();
        cout << "\nPhone       : " << User.GetPhone();
        cout << "\nFull Name   : " << User.GetFullName();
        cout << "\nUser Name   : " << User.GetUserName();
        cout << "\nPassword    : " << User.GetPassword();
        cout << "\nPermissions : " << User.GetPermissions();
        cout << "\n___________________\n";
    }
};