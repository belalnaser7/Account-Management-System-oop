#pragma once
#include <string>
#include <iostream>
#include "Currencies.h"
#include "ClsScreen.h"
#include "PrintAccount.h"
#include "/Users/dell/Desktop/libraries/ClsInputValidate.h"
#define RED "\033[31m"
#define RESET "\033[0m"
#define GREEN "\033[32m"
using namespace std;
class UpdateCurrencyRate : protected ClsScreen
{
    static bool _FindByCode(string &code)
    {
        int count = 0;
        while (count < 3)
        {
            code = clsInputValidate::ReadString("Enter Code to Find Currency: ");
            if (ClsCurrencies::isFoundByCode(clsInputValidate::UpperString(code)))
            {

                return true;
            }
            count++;
            cout << RED << "Currency not found. Attempts left: " << (3 - count) << RESET << "\n";
        }
        // cout<<RED<<"You have exceeded the maximum number of attempts.\n"<<RESET;
        return false;
    }

public:
    static void UpdateRate()
    {
        DisplayScreenTitle("Update Currency Rate");
        string code;
        if (_FindByCode(code))
        {
            cout << GREEN << "Currency found :-\n"
                 << RESET;
            ClsCurrencies currency = ClsCurrencies::FindCurrenciesByCode(clsInputValidate::UpperString(code));
            ClsPrintCurrencies::PrintCurrrencyCard(currency);
            float rate = clsInputValidate::readfloat("Enter New Rate: ");
            currency.UpdateRate(clsInputValidate::UpperString(code), rate);
            currency.SetRate(rate);
            cout << GREEN << "Rate Updated Successfully.\n"
                 << RESET;
            ClsPrintCurrencies::PrintCurrrencyCard(currency);
        }
        else
        {
            cout << RED << "Currency not found.\n"
                 << RESET;
        }
    }
};