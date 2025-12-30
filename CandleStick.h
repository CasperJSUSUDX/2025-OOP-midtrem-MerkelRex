#pragma once

#include <string>
#include <vector>

struct candlestickEntry
{
    std::string startTimestamp;
    std::string endTimestamp;
    double open;
    double high;
    double low;
    double close;
};

/** x is from left to right
 *  y is from top to bottom
 */
using canvas = std::vector<std::string>;

class Candlestick
{
    public:
        Candlestick();
        /** print out a list of candle stick information by the input vector */
        static void printCandlestick(std::vector<candlestickEntry> candlesticks);

        std::string date;
        double open;
        double high;
        double low;
        double close;
};