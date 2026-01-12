#pragma once
#include <iostream>
#include "ClsBankClient.h"
#include "ClsScreen.h"
#include "/Users/dell/Desktop/libraries/ClsInputValidate.h"
using namespace std;
class AddNewClient :protected ClsScreen
{
private:
  static void ReadClientData(ClsBankClient &client)
{
   cout << "Enter First Name: ";
   client.SetFristName(clsInputValidate::ReadString());
   cout << "Enter Last Name: ";
   client.SetLastName(clsInputValidate::ReadString());
   cout << "Enter Email: ";
   client.SetEmail(clsInputValidate::ReadString());
   cout << "Enter Phone Number: ";
   client.SetPhone(clsInputValidate::ReadString());
   cout << "Enter PinCode: ";
   client.SetPincode(clsInputValidate::ReadString());
   client.SetAccountBalance(clsInputValidate::readnumber("Enter Account Balance: "));
}
public:
static void AddNewAccount(){
    ClsScreen::DisplayScreenTitle("Add New Client Screen");
    int count = 0;
    int accNum=0;
    while(count<3){
     accNum = clsInputValidate::readnumber("Enter Account Number to AddNewAccount: ");
     if(ClsBankClient::IsFound(accNum)){
        cout << "Account already exists. Please try again.\n";
        count++;
     }
     else{
        ClsBankClient client = ClsBankClient::AddObjectToFile(accNum);
        ReadClientData(client);
        switch (client.SaveToFile())
        {
        case ClsBankClient::enSaveMode::SaveSucceded:
           cout << "Account added successfully.\n";
           client.Print();
           break;
        case ClsBankClient::enSaveMode::svFaildedAccountExists:
           cout << "Account already exists. Please try again.\n";
           client.Print();
           break;
        case ClsBankClient::enSaveMode::svFaildedAccountEmpty:
           cout << "Failed to add account. Account data is empty.\n";
           break;
        default:
           break;
        }
        break;

     }
    }
    if(count>=3){
        cout << "You have exceeded the maximum number of attempts.\n";
    }
   
}
};

