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
class CurrencyCalculator : protected ClsScreen
{

    static bool _FindByCode(string &code,string &string)
    {
        int count = 0;
        while (count < 3)
        {
            code = clsInputValidate::ReadString(string);
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
    static void currencyCalculator()
    {
        DisplayScreenTitle("Currency Calculator");
        do
        {
            string code1;
            string code2;
            string to="Enter Code of Currency to Convert From: ";
            string from="Enter Code of Currency to Convert To: ";
            int amount1 = 0;
            int amount2 = 0;
            if (_FindByCode(code1,to))
            {
                cout << GREEN << "Currency found :-\n"
                     << RESET;
                ClsCurrencies currency1 = ClsCurrencies::FindCurrenciesByCode(clsInputValidate::UpperString(code1));
                if (_FindByCode(code2,from))
                {
                    cout << GREEN << "Currency found :-\n"
                         << RESET;
                    ClsCurrencies currency2 = ClsCurrencies::FindCurrenciesByCode(clsInputValidate::UpperString(code2));
                }
                else
                {
                    cout << RED << "Currency not found.\n"
                         << RESET;
                    return;
                }
                float amount = clsInputValidate::readfloat("Enter Amount: ");
                ClsPrintCurrencies::PrintCurrrencyCard(currency1);
                amount1 = ClsCurrencies::GetCurrencyRateByUSD(amount, clsInputValidate::UpperString(code1));
                cout << amount << "=" << amount1 << "USD\n";
                if (ClsCurrencies::IsConversionToUSD(clsInputValidate::UpperString(code2)))
                {
                    ClsCurrencies currency2 = ClsCurrencies::FindCurrenciesByCode(clsInputValidate::UpperString(code2));
                    ClsPrintCurrencies::PrintCurrrencyCard(currency2);
                    amount2 = ClsCurrencies::GetCurrencyRateAfterConversion(amount1, clsInputValidate::UpperString(code2));
                    cout << amount << currency1.GetCurrencyCode() << "=" << amount2 << currency2.GetCurrencyCode() << "\n";
                }
                cout << "Do You Want To Perform Another Operation? (Y/N)\n";
            }
            else
            {
                cout << RED << "Currency not found.\n"
                     << RESET;
                return;
            }

        } while (clsInputValidate::boolread());
    }
};