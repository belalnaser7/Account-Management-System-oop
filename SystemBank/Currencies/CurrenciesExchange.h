#pragma once
#include <string>
#include "/Users/dell/Desktop/libraries/ClsInputValidate.h"
#include "ClsScreen.h"
#include "CurrenciesList.h"
#include "FindCurrency.h"
#include "UpdateCurrencyRate.h"
#include "CurrencyCalculator.h"
using namespace std;
class ClsCurrenciesExchange:protected ClsScreen{
    enum Ecurrencies{
        eCurrenciesList=1,
        eCurrenciesFind=2,
        eCurrenciesUpdate=3,
        eCurrenciesCalclute=4,
        eMainMenu=5
    };
     static void _CurrenciesExchangeMenu()
    {
        cout <<Blue<< "\t\t\t\t\t[1]<<"<<RESET<<" List Currencies.\n";
        cout <<Blue<< "\t\t\t\t\t[2]<<"<<RESET<<" Find Currency.\n";
        cout <<Blue<< "\t\t\t\t\t[3]<<"<<RESET<<" Update Currency Rate.\n";
        cout <<Blue<< "\t\t\t\t\t[4]<<"<<RESET<<" Currency Calculator.\n";
        cout <<Blue<< "\t\t\t\t\t[5]<<"<<RESET<<" Main Menu.\n";
        cout << "\t\t\t\t=========================================\n";
    }
static void _PerformCurrenciesExchangeOption(Ecurrencies Option)
    {
        switch (Option)
        {
        case eCurrenciesList:
            system("cls");
            ClsCurrenciesList::DisplayCurrenciesList();
            break;
        case eCurrenciesFind:
            system("cls");
            FindCurrencies::ShowFindCurrency();
            break;
        case eCurrenciesUpdate:
            system("cls");
            UpdateCurrencyRate::UpdateRate();
            break;
        case eCurrenciesCalclute:
            system("cls");
            CurrencyCalculator::currencyCalculator();
            break;
        case eMainMenu:
           // system("cls");
            break;
        default:
            break;
        }
    }
    public:
    static void DisplayCurrenciesExchange(){
        if(!CheckAccessRights(ClsUser::enPermissions::pCurranciesExchange)){
            BlockScreenDisplay("\033[31mYou Don't Have Permission to Currencies Exchange\033[0m");
            return;
        }
       
         bool exit = false;
        while (!exit)
        {
            system("cls");
            DisplayScreenTitle("Currencies Exchange Screen");
           _CurrenciesExchangeMenu();
            int Option = clsInputValidate::ReadIntNumberBetween("Choose what you want to do (1-5): ", 1, 5);
            _PerformCurrenciesExchangeOption((Ecurrencies)Option);
            if (Option == eMainMenu)
            {
                exit = false;
                break;
            }
            cout <<RED<< "press any key to continue..."<<RESET;
           cin.ignore();
           cin.get();
        }
    }
};