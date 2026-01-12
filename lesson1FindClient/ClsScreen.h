#pragma once
#include <iostream>
using namespace std;
class ClsScreen
{
protected:
    static void DisplayScreenTitle(string title)
    {
        
        cout << "\n\t\t\t\t=========================================\n";
        cout << "\t\t\t\t\t\t" << title << "\n";
        cout << "\t\t\t\t=========================================\n";

    }
};
