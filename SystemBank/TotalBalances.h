#pragma once
#include <iostream>
#include "ClsBankClient.h"
#include "/Users/dell/Desktop/libraries/ClsInputValidate.h"
#include "ClsScreen.h"
using namespace std;
class ClsTotalBalances : protected ClsScreen
{
public:
    static void ShowTotalBalances()
    {
        ClsScreen::DisplayScreenTitle("Total Balances Screen");
        int total = ClsBankClient::totalBalances();
        int numberOfClients = ClsBankClient::NumberOfClientsCount();
        cout << "\n\t\t\t\tTotal Balances of All Clients: " << total << " Dollars" << "\n";
        cout << "\n\t\t\t\tNumber of Clients: " << numberOfClients << "\n";
    }
};