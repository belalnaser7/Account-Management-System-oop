#pragma once 
#include <iostream>
#include "ClsMainScreen.h"
#include "ClsUser.h"
#include "/Users/dell/Desktop/libraries/ClsInputValidate.h"
#include "ClsScreen.h"
#include "Global.h"
using namespace std;
class Login :protected ClsScreen
{
public:
 static void LoginScreen()
   {
    system("cls");
    DisplayScreenTitle("Login Screen");
    string UserName;
    int Password;
    int count = 0;
    do
       {
        
        UserName = clsInputValidate::ReadString("Enter UserName: ");
        Password = clsInputValidate::readnumber("Enter Password: ");
       CurrentUser = ClsUser::Find(UserName, Password);
        if (!CurrentUser.IsEmpty())
        {
          cout << "\033[32mLogin Successful\033[0m" << endl;
          cout << "\033[32mWelcome " << CurrentUser.GetFullName() << "\033[0m" << endl;
          cout << "\033[32mYou Have " << CurrentUser.GetPermissions() << " Permissions\033[0m" << endl;
          cout << "\033[32mHave A Nice Day .\033[0m\n press Enter to Open the System....."  ;
          cin.ignore();
          cin.get();
        
       CurrentUser.SaveDataOFLogsToFile();
          ClsMainScreen::ShowMainScreen();
          return;
        }
         
        else
          cout << "\033[31mInvalid UserName or Password\033[0m" << endl;
           count++;
       } while (count < 3);
       cout<<"You Are Dirty Person👎\n";
   }

  
};