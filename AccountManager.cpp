#include "AccountManager.h"
#include "CSVReader.h"
#include <iostream>
#include <fstream>
#include <vector>

AccountManager::AccountManager() {}

bool AccountManager::login()
{
    while (true)
    {
        loadAccounts("accounts.csv");
        std::hash<std::string> hasher;
        std::string username;
        std::string password;
        std::cout << "Please login in your account." << std::endl;
        std::cout << "Username: " << std::ends;
        std::cin >> username;
        if (findUsername(username))
        {
            std::cout << "Password: " << std::ends;
            std::cin >> password;
            if (hasher(password) == cache[username].password_h)
            {
                std::cout << "Login in successfully" << std::endl;
            }
            else
            {
                std::cout << "Wrong password. Please try again." << std::endl;
                continue;
            }
        }
        else
        {
            std::string answer;
            std::cout << "This user name is not exist.\nDo u want to create a account with this name or try again. (Input retry or create)" << std::endl;
            while (true)
            {
                std::cin >> answer;
                if (answer != "retry" && answer != "create")
                {
                    std::cout << "Unknown answer, please try again." << std::endl;
                }
                else
                {
                    break;
                }
            }
            
            if (answer == "create")
            {
                createAccount(username);
                return false;
            }
            else
            {
                continue;
            }
        }

        return true;
    }
}

void AccountManager::createAccount(std::string username)
{
    std::hash<std::string> hasher;
    std::string password;
    std::string email;
    if (username == "") {}
    std::cout << "Username: " << username << std::endl;
    std::cout << "Please set a password." << std::endl;
    std::cout << "Password: " << std::ends;
    std::cin >> password;
    std::cout << "Please connect an email." << std::endl;
    std::cout << "Email: " << std::ends;
    std::cin >> email;
    UserInfo info = {hasher(password), email};
    cache[username] = info;
    updateUserCSV();
}

void AccountManager::loadAccounts(std::string filename)
{
    cache.clear();
    std::hash<std::string> hasher;
    std::fstream accounts(filename);
    if (accounts.is_open())
    {
        std::string line;
        while (std::getline(accounts, line))
        {
            std::vector<std::string> tokens = CSVReader::tokenise(line, ',');
            UserInfo info = { std::stoull(tokens[1]), tokens[2] };
            cache[tokens[0]] = info;
        }

        accounts.close();
    }
}

void AccountManager::updateUserCSV()
{
    std::ofstream accounts("accounts.csv", std::ios::out | std::ios::trunc);
    if (accounts.is_open())
    {
        for (auto& data: cache)
        {
            std::string username = data.first;
            std::string password = std::to_string(data.second.password_h);
            std::string email = data.second.email;
            std::string newLine = username + ',' + password + ',' + email + '\n';
            accounts << newLine;
        }

        accounts.close();
    }
}

bool AccountManager::findUsername(std::string username)
{
    return cache.find(username) != cache.end();
}

std::map<std::string, UserInfo> AccountManager::cache;