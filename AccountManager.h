#pragma once

#include <string>
#include <map>
#include <set>

struct UserInfo
{
    std::size_t password_h;
    std::string email;
};

class AccountManager
{
    public:
        AccountManager();
        static bool login();
        static void createAccount(std::string username);
    private:
        static void loadAccounts(std::string filename);
        static void updateUserCSV();
        static bool findUsername(std::string username);
        static std::map<std::string, UserInfo> cache;
};
