#include <iostream>
#include "Login.h"
#include "/Users/dell/Desktop/libraries/ClsInputValidate.h"
using namespace std;
int main()
{
  bool exit = false;

  do
  {
    Login::LoginScreen();
    cout << "Do you want to login again? (Y/N):\n ";
    exit = clsInputValidate::boolread();

  } while (exit);

  return 0;
}