#include "CandleStickEntry.h"
#include "CSVReader.h"
#include <iostream>
#include <vector>

CandleStickEntry::CandleStickEntry(
    std::string _date,
    double _open,
    double _high,
    double _low,
    double _close)
: date(_date),
  open(_open),
  high(_high),
  low(_low),
  close(_close)
{

}

void CandleStickEntry::print()
{
    std::cout << "Current time: " << date << std::endl;
    std::cout << "Open: " << open << std::endl;
    std::cout << "High: " << high << std::endl;
    std::cout << "Low: " << low << std::endl;
    std::cout << "Close: " << close << std::endl;
    std::cout << "===================" << std::endl;
}

std::string CandleStickEntry::getDate(DateRange dateRange)
{
    std::vector<std::string> dates = CSVReader::tokenise(date, '/');
    switch (dateRange)
    {
    case DateRange::YEARLY:
        return date.substr(0, 4);
    case DateRange::MONTHLY:
        return date.substr(0, 7);
    case DateRange::DAILY:
        return date.substr(0, 10);
    default:
        return date.substr(0, 4);
    }
}