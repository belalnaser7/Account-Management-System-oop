#pragma once
#include <iostream>
#include "ClsBankClient.h"
#include "ClsScreen.h"
#include "PrintAccount.h"
#include "/Users/dell/Desktop/libraries/ClsInputValidate.h"
#define RED "\033[31m"
#define RESET "\033[0m"
#define GREEN "\033[32m"
#define Cryan "\033[36m"
using namespace std;
class AddNewClient : protected ClsScreen
{
private:
   static void ReadClientData(ClsBankClient &client)
   {
      client.SetFirstName(clsInputValidate::ReadString("\033[36mEnter First Name: \033[0m"));
      client.SetLastName(clsInputValidate::ReadString("\033[36mEnter Last Name: \033[0m"));
      client.SetEmail(clsInputValidate::ReadString("\033[36mEnter Email: \033[0m"));
      client.SetPhone(clsInputValidate::ReadString("\033[36mEnter Phone Number: \033[0m"));
      client.SetPincode(clsInputValidate::ReadString("\033[36mEnter PinCode: \033[0m"));
      client.SetAccountBalance(clsInputValidate::readnumber("\033[36mEnter Account Balance: \033[0m"));
       cout << GREEN << "\nAll inputs recorded successfully!" << RESET << endl;
   }

public:
   static void AddNewAccount()
   {
      if (!CheckAccessRights(ClsUser::enPermissions::pAddClient))
      {
         BlockScreenDisplay("\033[31mYou Don't Have Permission to Add New Client\033[0m");
         return;
      }
      ClsScreen::DisplayScreenTitle("Add New Client Screen");
      int count = 0;
      int accNum = 0;
      while (count < 3)
      {
         accNum = clsInputValidate::readnumber("Enter Account Number to AddNewAccount: ");
         if (ClsBankClient::IsFound(accNum))
         {
            cout <<RED<< "Account already exists. Please try again.\n"<<RESET;
            count++;
         }
         else
         {
            ClsBankClient client = ClsBankClient::AddObjectToFile(accNum);
            ReadClientData(client);
            switch (client.SaveToFile())
            {
            case ClsBankClient::enSaveMode::SaveSucceeded:
               cout <<GREEN<< "Account added successfully.\n"<<RESET;
               ClsPrintAccount::PrintAccountCard(client);
               break;
            case ClsBankClient::enSaveMode::svFaildedAccountExists:
               cout <<RED<< "Account already exists. Please try again.\n"<<RESET;
               ClsPrintAccount::PrintAccountCard(client);
               break;
            case ClsBankClient::enSaveMode::svFaildedAccountEmpty:
               cout <<RED<< "Failed to add account. Account data is empty.\n"<<RESET;
               break;
            default:
               break;
            }
            break;
         }
      }
      if (count >= 3)
      {
         cout <<RED<< "You have exceeded the maximum number of attempts.\n"<<RESET;
      }
   }
};
