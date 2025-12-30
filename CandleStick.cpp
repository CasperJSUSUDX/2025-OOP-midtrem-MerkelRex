// Made by myself - start
#include "Candlestick.h"
#include "CSVReader.h"
#include <iostream>
#include <vector>

Candlestick::Candlestick()
{
}

void Candlestick::printCandlestick(std::vector<candlestickEntry> candlesticks)
{   
    if (candlesticks.empty()) return;

    for (candlestickEntry& cse: candlesticks)
    {
        std::cout << cse.startTimestamp << " --> " << cse.endTimestamp << "\n" << std::endl;

        // up day
        if (cse.close >= cse.open) 
        {
            // Made by myself - end
            std::cout << "\033[32m";
            // Made by myself - start
            std::cout << "High: " << cse.high << std::endl;
            std::cout << "Close: " << cse.close << std::endl;
            std::cout << "Open: " << cse.open << std::endl;
            std::cout << "Low: " << cse.low << std::endl;
        }
        // down day
        if (cse.close < cse.open) 
        {
            // Made by myself - end
            std::cout << "\033[31m";
            // Made by myself - start
            std::cout << "High: " << cse.high << std::endl;
            std::cout << "Open: " << cse.open << std::endl;
            std::cout << "Close: " << cse.close << std::endl;
            std::cout << "Low: " << cse.low << std::endl;
        }

        // stop color text
        // Made by myself - end
        std::cout << "\033[0m";
        // Made by myself - start
        std::cout << "==============" << std::endl;
    }
}
// Made by myself - end