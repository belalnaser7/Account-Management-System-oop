#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "/Users/dell/Desktop/libraries/ClsDate.h"
#include "/Users/dell/Desktop/libraries/Clsstring.h"
 #include "/Users/dell/Desktop/libraries/Utility.h"
#include "ClsPerson.h"
#include <ctime>
#if 1
#define ENUMERATIONS 1
#define Member_Variables 1
#define Empty_User_Object 1
#define Transfer_To_Line_And_Save_In_File 1
#define Serialize 1
#define Save_Accounts_To_File 1
#define Deserialize 1
#define Load_Accounts_From_File 1
#define Constructor 1
#define To_Update 1
#define To_Add 1
#define To_Delete 1
#define To_Find 1
#define To_SAVE 1
#define Getters_Setters 1
#define Check_If_Object_Is_Empty 1
#endif
using namespace std;
class ClsUser : public ClsPerson
{
    public:
       struct stLoginRegisterRecord
    {
        string Date;
        string Time;
        string UserName;
        string Password;
        int Permissions;

    };
private:
#if ENUMERATIONS
    enum enMode
    {
        EmptyMode = 0,
        UpdateMode = 1,
        AddMode = 2
    };
    enum enFields
    {
        FldFirstName = 0,
        FldLastName = 1,
        FldEmail = 2,
        FldPhone = 3,
        FldUserName = 4,
        FldPassword = 5,
        FldPermissions = 6
    };
    enum enFieldsLogs
    {
        Date = 0,
        Time = 1,
        UserName = 2,
        Password = 3,
        Permissions = 4
    };
  
#endif
#if Member_Variables
    enMode _Mode;
    string _UserName;
    string _Password;
    int _permissions;
    bool _IsMarkedForDelete = false;
   
   
#endif
#if Empty_User_Object
    static ClsUser _GetEmptyUserObject()
    {
        return ClsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }
#endif
#if Transfer_To_Line_And_Save_In_File
#if Serialize
    string _SerlizeDataOFLogs(string dellem = "#//#")
    {
        return ClsDate::Gettodaydate() + dellem +
               ClsDate::Gettodaytime() + dellem +
               _UserName + dellem +
               clsUtility::EncryptText(_Password) + dellem +
               to_string(_permissions);
    }
    static string _SerializeAccount(const ClsUser &User)
    {
        return User.GetFirstName() + "," +
               User.GetLastName() + "," +
               User.GetEmail() + "," +
               User.GetPhone() + "," +
               User.GetUserName() + "," +
               clsUtility::EncryptText(User.GetPassword()) + "," +
               to_string(User.GetPermissions());
    }
#endif
#if Save_Accounts_To_File

    static void _SaveAccountsToFile(const vector<ClsUser> &Users)
    {
        string line;
        ofstream fout("User.txt", ios::trunc); // Open file in truncate mode to overwrite existing content
        for (const auto &User : Users)
        {
            if (User._IsMarkedForDelete)
                continue; // Skip Users marked for deletion
            line = _SerializeAccount(User);
            fout << line << endl;
        }
        fout.close();
    }
#endif
#endif
#if Deserialize

    static stLoginRegisterRecord _Deserializelogs(const string &line)
    {
        vector<string> parts = ClsString::Split(line, "#//#");
        stLoginRegisterRecord LoginRegisterRecord;
        if (parts.size() != 5)
        {
            return LoginRegisterRecord;
        }
        LoginRegisterRecord.Date = parts[enFieldsLogs::Date] ;
        LoginRegisterRecord.Time=parts[enFieldsLogs::Time];
        LoginRegisterRecord.UserName = parts[enFieldsLogs::UserName];
        LoginRegisterRecord.Password = clsUtility::DecryptText(parts[enFieldsLogs::Password]);
        LoginRegisterRecord.Permissions = stoi(parts[enFieldsLogs::Permissions]);
        return LoginRegisterRecord;
       
       
    }
    static ClsUser _deserializeAccount(const string &line)
    {
        vector<string> parts = ClsString::Split(line, ",");
        if (parts.size() != 7)
        {
            return _GetEmptyUserObject();
        }
        int Permissions = 0;
        try
        {
            Permissions = stoi(parts[enFields::FldPermissions]);
        }
        catch (...)
        {
            Permissions = -1;
        }
        // Construct object in UpdateMode (real User)
        return ClsUser(
            enMode::UpdateMode,
            parts[enFields::FldFirstName], // FirstName
            parts[enFields::FldLastName],  // LastName
            parts[enFields::FldEmail],     // Email
            parts[enFields::FldPhone],     // Phone
            parts[enFields::FldUserName],  // UserName
            clsUtility::DecryptText(parts[enFields::FldPassword]),  // Password
            Permissions                    // permissions
        );
    }
#endif
#if Load_Accounts_From_File

static vector<stLoginRegisterRecord> _LoadLogsFromFile(){
    vector<stLoginRegisterRecord> VloginRegisterRecord;
    fstream fin("Logs.txt");
    if (!fin.is_open())
        return VloginRegisterRecord;
    string line;
    stLoginRegisterRecord LoginRegisterRecord;  
    while (getline(fin, line))
    {
        if (line.empty())
            continue;
       LoginRegisterRecord= _Deserializelogs(line);
       VloginRegisterRecord.push_back(LoginRegisterRecord);
    }
    fin.close();
    return VloginRegisterRecord;
}
    static vector<ClsUser> _LoadAccountsFromFile()
    {
        vector<ClsUser> VUser;
        fstream fin("User.txt");
        if (!fin.is_open())
            return VUser;
        string line;
        while (getline(fin, line))
        {
            if (line.empty())
                continue;
            VUser.push_back(_deserializeAccount(line));
        }
        fin.close();
        return VUser;
    }
#endif
#if To_Update
    void _update()
    {
        vector<ClsUser> Users = _LoadAccountsFromFile();

        for (auto &User : Users)
        {
            if (User.GetUserName() == GetUserName())
            {
                User = *this;
                break;
            }
        }
        _SaveAccountsToFile(Users);
    }
#endif
#if To_Add
    void _AddNewAccount()
    {
        vector<ClsUser> Users = _LoadAccountsFromFile();
        Users.push_back(*this);
        _SaveAccountsToFile(Users);
        _Mode = enMode::AddMode;
    }
#endif
public:
#if Constructor
ClsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, int permissions) : ClsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _permissions = permissions;
    }
 #else
    ClsUser(string date, string time, string UserName, string Password, string permissions): ClsPerson("", "", "", "") {
   
    _Date= date;
    _Time= time;
    _UserName = UserName;
    _Password = Password;
    _permissions = stoi(permissions);
 };
#endif
#if Getters_Setters
    string GetUserName() const { return _UserName; }
    string GetPassword() const { return _Password; }
    int GetPermissions() const { return _permissions; }

    void SetUserName(string UserName) { _UserName = UserName; }
    void SetPassword(string Password) { _Password = Password; }
    void SetPermissions(int permissions) { _permissions = permissions; }
#endif
#if Check_If_Object_Is_Empty
    bool IsEmpty() const
    {
        return (_Mode == EmptyMode);
    }
#endif
#if To_Find
    static ClsUser Find(string User)
    {
        vector<ClsUser> Users = _LoadAccountsFromFile();
        for (auto &Account : Users)
        {
            if (User == Account.GetUserName())
                return Account;
        }
        return _GetEmptyUserObject();
    }
    // Find by AccountNumber + Password
    static ClsUser Find(string User, const int &password)
    {
        vector<ClsUser> Users = _LoadAccountsFromFile();
        for (auto &Account : Users)
        {
            if (User == Account.GetUserName() &&
                to_string(password) == Account.GetPassword())
                return Account;
        }
        return _GetEmptyUserObject();
    }
    // Check if account exists (by AccountNumber)
    static bool IsFound(string user)
    {
        ClsUser Account = Find(user);
        return !Account.IsEmpty();
    }
    // Check if account exists (by AccountNumber + password)
    static bool IsFound(string User, const int &pass)
    {
        ClsUser Account = Find(User, pass);
        return !Account.IsEmpty();
    }
#endif
#if ENUMERATIONS
    enum enPermissions
    {
        pAll = -1,
        pListClients = 1,
        pAddClient = 2,
        pUpdateClient = 4,
        pDeleteClient = 8,
        pFindClient = 16,
        pTranactions = 32,
        pManageUsers = 64,
        pShowLogs = 128
    };
    enum enSaveMode
    {
        svFaildedAccountEmpty = 0,
        SaveSucceeded = 1,
        svFaildedAccountExists = 2
    };
#endif
#if To_SAVE
    enSaveMode SaveToFile()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
            return enSaveMode::svFaildedAccountEmpty;
        case enMode::UpdateMode:
            _update();
            return enSaveMode::SaveSucceeded;
        case enMode::AddMode:
            if (ClsUser::IsFound(GetUserName()))
            {
                return enSaveMode::svFaildedAccountExists;
            }
            else
            {
                _AddNewAccount();
                _Mode = enMode::UpdateMode;
                return enSaveMode::SaveSucceeded;
            }
        }
        return enSaveMode::svFaildedAccountEmpty;
    }
#endif
#if To_Add
    static ClsUser AddObjectToFile(string UserName)
    {
        return ClsUser(enMode::AddMode, "", "", "", "", UserName, "", 0);
    }
#endif
#if Get_Users_List
    static vector<ClsUser> GetUsersList()
    {
        return _LoadAccountsFromFile();
    }
#endif
#if To_Delete
    bool Delete()
    {
        vector<ClsUser> Users = _LoadAccountsFromFile();
#if 0 // this is method using MarkedForDelete
            for (auto &&i : Users)
            {
                if (i.GetUserName() == _AccountNumber)
                {
                    i.MarkedForDelete = true;
                    break;
                }
            }
            _SaveAccountsToFile(Users);
            *this = _GetEmptyUserObject();
            return true;
#else // this is method using iterator
        for (auto it = Users.begin(); it != Users.end(); ++it)
        {
            if (it->GetUserName() == GetUserName())
            {
                Users.erase(it);
                _SaveAccountsToFile(Users);
                *this = _GetEmptyUserObject();
                return true;
            }
        }
        return false;
#endif
    }
#endif
    static vector<ClsUser> GetUsersLists()
    {
        return _LoadAccountsFromFile();
    }
    
    bool CheckAccessPermission(enPermissions Permission)
    {
        if (this->_permissions == pAll)
            return true;

        if (this->_permissions & Permission)
            return true;
        else
            return false;
    }

    void SaveDataOFLogsToFile()
    {
        string line;
        ofstream fout("Logs.txt", ios::app);
        line = _SerlizeDataOFLogs();
        fout << line << endl;
        fout.close();
    }

    static vector<stLoginRegisterRecord> GetLogsLists()
    {
        return _LoadLogsFromFile();
    }
};