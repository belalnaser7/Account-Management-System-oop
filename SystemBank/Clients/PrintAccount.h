#pragma once
#include <iostream>
#include "ClsBankClient.h"
#include "ClsUser.h"
#include "Currencies.h"
#define Cyan "\033[36m"
#define RESET "\033[0m"
#define Blue "\033[34m"
using namespace std;
class ClsPrintAccount
{
public:
    static void PrintAccountCard(const ClsBankClient &client)
    {
        cout << Blue << "\nClient Card:" << RESET;
        cout << "\n___________________";
        cout << Cyan << "\nFirstName   : " << RESET << client.GetFirstName();
        cout << Cyan << "\nLastName    : " << RESET << client.GetLastName();
        cout << Cyan << "\nEmail       : " << RESET << client.GetEmail();
        cout << Cyan << "\nPhone       : " << RESET << client.GetPhone();
        cout << Cyan << "\nFull Name   : " << RESET << client.GetFullName();
        cout << Cyan << "\nAcc. Number : " << RESET << client.GetAccountNumber();
        cout << Cyan << "\nBalance     : " << RESET << client.GetAccountBalance();
        cout << "\n___________________\n";
    }
};

class ClsPrintUsers
{
public:
    static void PrintUserCard(const ClsUser &User)
    {
        cout << Blue << "\nUser Card:" << RESET;
        cout << "\n___________________";
        cout << Cyan << "\nFirstName   : " << RESET << User.GetFirstName();
        cout << Cyan << "\nLastName    : " << RESET << User.GetLastName();
        cout << Cyan << "\nEmail       : " << RESET << User.GetEmail();
        cout << Cyan << "\nPhone       : " << RESET << User.GetPhone();
        cout << Cyan << "\nUser Name   : " << RESET << User.GetUserName();
        cout << Cyan << "\nPassword    : " << RESET << User.GetPassword();
        cout << Cyan << "\nPermissions : " << RESET << User.GetPermissions();
        cout << "\n___________________\n";
    }
};

class ClsPrintTransaction
{
public:
    static void PrintTransactionCard(const ClsBankClient &client)
    {
        cout << Blue << "\nClient Card:" << RESET;
        cout << "\n___________________";
        cout << Cyan << "\nFull Name   : " << client.GetFullName() << RESET;
        cout << Cyan << "\nAcc. Number : " << client.GetAccountNumber() << RESET;
        cout << Cyan << "\nBalance     : " << client.GetAccountBalance() << RESET;
        cout << "\n___________________\n";
    }
};

class ClsPrintCurrencies
{
public:
    static void PrintCurrrencyCard(const ClsCurrencies &currency)
    {
        cout << Blue << "\nCurrency Card:" << RESET;
        cout << "\n___________________";
        cout << Cyan << "\nCountry Name   : " << RESET << currency.GetConuntryName();
        cout << Cyan << "\nCurrency Code  : " << RESET << currency.GetCurrencyCode();
        cout << Cyan << "\nCurrency Name  : " << RESET << currency.GetCurrencyName();
        cout << Cyan << "\nRate           : " << RESET << currency.GetRate();
        cout << "\n___________________\n";
    }
};
