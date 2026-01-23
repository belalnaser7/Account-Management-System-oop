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
class FindCurrencies:protected ClsScreen{
    enum _enFind{
        eFindBycode=1,
        eFindBycountryName=2
    };
    static void _FindByCode(){
        int count=0;
        while (count<3)
        {
            string code=clsInputValidate::ReadString("Enter Code to Find Currency: ");
            if (ClsCurrencies::isFoundByCode(clsInputValidate::UpperString(code))){
                cout<<GREEN<<"Currency found :-\n"<<RESET;
                ClsCurrencies currency=ClsCurrencies::FindCurrenciesByCode(clsInputValidate::UpperString(code));
                ClsPrintCurrencies::PrintCurrrencyCard(currency);
                return;
            }
            count++;
            cout<<RED<<"Currency not found. Attempts left: "<<(3-count)<<RESET<<"\n";
        }
        cout<<RED<<"You have exceeded the maximum number of attempts.\n"<<RESET;
    }
    static void _FindByCountryName(){
        int count=0;
        while (count<3)
        {
            string countryName=clsInputValidate::ReadString("Enter Country Name to Find Currency: ");
            if (ClsCurrencies::isFoundByCountry(clsInputValidate::UpperString(countryName))){
                cout<<GREEN<<"Currency found :-\n"<<RESET;
                ClsCurrencies currency=ClsCurrencies::FindCurrenciesByCountry(clsInputValidate::UpperString(countryName));
                ClsPrintCurrencies::PrintCurrrencyCard(currency);
                return;
            }
            count++;
            cout<<RED<<"Currency not found. Attempts left: "<<(3-count)<<RESET<<"\n";
        }
        cout<<RED<<"You have exceeded the maximum number of attempts.\n"<<RESET;
    }

    static void _PerformFind(int option){
        switch (option)
        {
        case eFindBycode:
            _FindByCode();
            break;
        case eFindBycountryName:
            _FindByCountryName();
            break;
        default:
            break;
        }
        
    }

    public:
    static void ShowFindCurrency(){
        DisplayScreenTitle("Find Info Currency");
        cout<<"1)Search By Code\n2)Search By Country Name\n";
        int choice=clsInputValidate::ReadIntNumberBetween("Choose what you want to do (1-2): ", 1, 2);
        _PerformFind(choice);

    }
};