#pragma once

#include "Wallet.h"
#include <string>
#include <map>
#include <set>

struct UserInfo
{
    std::string username;
    std::size_t password_h;
    std::string email;
};

class AccountManager
{
    public:
        AccountManager();
        static Wallet login();
    private:
        static bool createAccount();
        static void loadAccounts(std::string filename);
        static void updateUserCSV();
        static Wallet getWallet(std::string uuid);
        static bool findUsername(std::string username);
        static bool resetPassword(std::string uuid);
        static std::string generateUUID(int length);
        static std::map<std::string, UserInfo> cache;
        static std::set<std::string> existUUID;
        static std::hash<std::string> hasher;
};
