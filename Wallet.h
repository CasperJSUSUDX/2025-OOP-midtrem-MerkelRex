#pragma once

#include "OrderBookEntry.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>

class Wallet 
{
    public:
        // Made by myself - start
        Wallet(std::string _uuid, std::string walletString);
        // Made by myself - end
        /** insert currency to the wallet */
        void insertCurrency(std::string type, double amount);
        /** remove currency from the wallet */
        bool removeCurrency(std::string type, double amount);
        
        /** check if the wallet contains this much currency or more */
        bool containsCurrency(std::string type, double amount);
        /** checks if the wallet can cope with this ask or bid.*/
        bool canFulfillOrder(OrderBookEntry order);
        /** update the contents of the wallet
         * assumes the order was made by the owner of the wallet
        */
        void processSale(OrderBookEntry& sale);
        // Made by myself - start
        /** log user transition and the balance */
        void logInCSV();
        // Made by myself - end

        /** generate a string representation of the wallet */
        std::string toString();
        friend std::ostream& operator<<(std::ostream& os, Wallet& wallet);
        // Made by myself - start
        /** convert to a format that can store in CSV and read by the code */
        std::string storeInString();

        /** this funciton will read the history csv and display a specific pieces by the arugment */
        void showTansitionOrTradingHistory(unsigned int pieces);
        /** this function will read the history csv and statistic all of the activity */
        void statisticsUserActivity();

        void updateUserWalletCSV();
        
        std::string uuid;
        
    private:
        // there are two format of the operate
        // if only have input or output: {action},{currency},{amount}
        // if have both input and output: {action},{outgoingCurrency},{outgoingAmount},{incomingCurrency},{incomingAmount}
        std::vector<std::string> operatesCache;
        // Made by myself - end
        std::map<std::string,double> currencies;
};
