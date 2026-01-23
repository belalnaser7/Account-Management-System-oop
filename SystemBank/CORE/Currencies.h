#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "/Users/dell/Desktop/libraries/ClsInputValidate.h"

#define Member_Variables 1
#define Setter_AND_Getter 1
#define To_Find 1
using namespace std;
class ClsCurrencies
{
#if Member_Variables
    enum enMode
    {
        EmptyMode = 0,
        UpdateMode = 1,
    };
    enMode _Mode;
    string _CountryName;
    string _CurrencyCode;
    string _CurrencyName;
    float _Rate;
#endif
    static ClsCurrencies _GetEmptyCurrencyObject()
    {
        return ClsCurrencies(enMode::EmptyMode, "", "", "", 0);
    }

    static ClsCurrencies _ConvertLineToObject(const string &line)
    {
        vector<string> parts = ClsString::Split(line, "#//#");
        if (parts.size() != 4)
        {
            return _GetEmptyCurrencyObject();
        }
        return ClsCurrencies(
            enMode::UpdateMode,
            parts[0],
            parts[1],
            parts[2],
            stof(parts[3]));
    }

    static vector<ClsCurrencies> _LoadRecordsFromFile()
    {
        vector<ClsCurrencies> Vcurrencies;
        fstream fin("Currencies.txt");
        if (!fin.is_open())
            return Vcurrencies;
        string Line = "";
        while (getline(fin, Line))
        {
            if (Line.empty())
                continue;
            Vcurrencies.push_back(_ConvertLineToObject(Line));
        }
        fin.close();
        return Vcurrencies;
    }

public:
    ClsCurrencies(enMode Mode, string CountryName, string CurrencyCode, string CurrencyName, float Rate)
    {
        _Mode = Mode;
        _CountryName = clsInputValidate::UpperString(CountryName);
        _CurrencyCode = clsInputValidate::UpperString(CurrencyCode);
        _CurrencyName = CurrencyName;
        _Rate = Rate;
    };

#if Setter_AND_Getter
    void SetRate(float Rate) { _Rate = Rate; }
    string GetConuntryName() const { return _CountryName; }
    string GetCurrencyName() const { return _CurrencyName; }
    string GetCurrencyCode() const { return _CurrencyCode; }
    float GetRate() const { return _Rate; }
#endif
    static vector<ClsCurrencies> GetCurrenciesList() { return _LoadRecordsFromFile(); }
#if To_Find
    static ClsCurrencies FindCurrenciesByCode(string CurrencyCode)
    {
        fstream Myfile("Currencies.txt",ios::in);
        if(Myfile.is_open()){
            string line="";
            while (getline(Myfile, line))
            {
                if (line.empty())
                    continue;
                ClsCurrencies Currency = _ConvertLineToObject(line);
                if(Currency.GetCurrencyCode() == CurrencyCode){
                     Myfile.close();
                    return Currency;
                }
            } 
        }
         Myfile.close();
        return _GetEmptyCurrencyObject();

    }
    static ClsCurrencies FindCurrenciesByCountry(string Country)
    {
        vector<ClsCurrencies> Vcurrencies = _LoadRecordsFromFile();
        for (auto &Currency : Vcurrencies)
        {
            if (Currency.GetConuntryName() == Country)
            {
                return Currency;
            }
        }
        return _GetEmptyCurrencyObject();
    }

    static bool isFoundByCode(string CurrencyCode)
    {
        ClsCurrencies currency = FindCurrenciesByCode(CurrencyCode);
        return !currency._Mode == enMode::EmptyMode;
    }
    static bool isFoundByCountry(string Country)
    {
        ClsCurrencies currency = FindCurrenciesByCountry(Country);
        return !currency._Mode == enMode::EmptyMode;
    }
#endif
void UpdateRate(string CurrencyCode, float Rate)
    {
        vector<ClsCurrencies> Vcurrencies = _LoadRecordsFromFile();
        for (auto &Currency : Vcurrencies)
        {
            if (Currency._CurrencyCode == CurrencyCode)
            {
                Currency.SetRate(Rate);
                break;
            }
        }
        fstream fout("Currencies.txt");
        for (auto &Currency : Vcurrencies)
        {
            fout << Currency._CountryName << "#//#";
            fout << Currency._CurrencyCode << "#//#";
            fout << Currency._CurrencyName << "#//#";
            fout << Currency._Rate << endl;
        }
        fout.close();
    }
    
    static float GetCurrencyRateAfterConversion(float Amount, string CurrencyCode)
    {
        ClsCurrencies currency = FindCurrenciesByCode(CurrencyCode);
        return Amount * currency._Rate;
    }
    static float GetCurrencyRateByUSD(float Amount, string CurrencyCode){
        ClsCurrencies currency = FindCurrenciesByCode(CurrencyCode);
        return Amount / currency.GetRate();
    }
    static bool IsConversionToUSD(string CurrencyCode)
    {
       if(CurrencyCode!= "USD")
       {
           return true;
       }
       return false;
    }


};