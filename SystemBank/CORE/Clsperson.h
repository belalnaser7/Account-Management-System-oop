#pragma once
#include <iostream>

using namespace std;

class ClsPerson
{
private:
    string _FirstName;
    string _LastName;
    string _Email;
    string _Phone;

public:
ClsPerson() {}
    ClsPerson(string _FirstName, string _LastName, string _Email, string _Phone)
    {
        this->_FirstName = _FirstName;
        this->_LastName = _LastName;
        this->_Email = _Email;
        this->_Phone = _Phone;
    }
   

    string GetFirstName() const
    {
        return _FirstName;
    }
    string GetLastName() const
    {
        return _LastName;
    }
    string GetEmail() const
    {
        return _Email;
    }
    string GetPhone() const
    {
        return _Phone;
    }
    void SetFirstName(string _FirstName)
    {
        this->_FirstName = _FirstName;
    }
    void SetLastName(string _LastName)
    {
        this->_LastName = _LastName;
    }
    void SetEmail(string _Email)
    {
        this->_Email = _Email;
    }
    void SetPhone(string _Phone)
    {
        this->_Phone = _Phone;
    }
    string GetFullName() const
    {
        return _FirstName + " " + _LastName;
    }
};