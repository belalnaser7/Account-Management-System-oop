#pragma once
#include <iostream>
#include "ClsScreen.h"
#include "Currencies.h"
#include <iomanip>
using namespace std;

class ClsCurrenciesList : protected ClsScreen
{
    static void PrintCurrenciesList(ClsCurrencies &Currency)
    {
        cout << "| " << setw(20) << left << Currency.GetConuntryName();
        cout << "| " << setw(12) << left << Currency.GetCurrencyCode();
        cout << "| " << setw(20) << left << Currency.GetCurrencyName();
        cout << "| " << setw(12) << left << Currency.GetRate();
    }

public:
    static void DisplayCurrenciesList()
    {
        DisplayScreenTitle("Show List Of Currencies");
        vector<ClsCurrencies> vCurrencies = ClsCurrencies::GetCurrenciesList();
        cout << "\n\t\t\t\t\tCurrency List (" << vCurrencies.size() << ") Currency(s).";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n";
        cout << "| " << left << setw(15) << "Country Name";
        cout << "| " << left << setw(12) << "Currency Code";
        cout << "| " << left << setw(15) << "Currency Name";
        cout << "| " << left << setw(12) << "Rate";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n";
        if (vCurrencies.size() == 0)
            cout << "\t\t\t\tNo Currencies Available In the System!";
        else
            for (auto &Currency : vCurrencies)
            {
                PrintCurrenciesList(Currency);
                cout << endl;
            }
    }
};