#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <vector>

OrderBookEntry::OrderBookEntry( double _price, 
                        double _amount, 
                        std::string _timestamp, 
                        std::string _product, 
                        OrderBookType _orderType, 
                        std::string _username)
: price(_price), 
  amount(_amount), 
  timestamp(_timestamp),
  product(_product), 
  orderType(_orderType), 
  username(_username)
{
  
    
}

unsigned int OrderBookEntry::calcIntervalByTimestamp(OrderBookEntry& e1, OrderBookEntry&e2)
{
  std::string timestamp1;
  std::string timestamp2;
  if (compareByTimestamp(e2, e1))
  {
    timestamp1 = e1.timestamp;
    timestamp2 = e2.timestamp;
  }
  else
  {
    timestamp1 = e2.timestamp;
    timestamp2 = e1.timestamp;
  }

  unsigned int interval = 0;
  // std::string day1 = timestamp1.substr(0, 10);
  std::string time1 = timestamp1.substr(11, 8);

  // std::string day2 = timestamp2.substr(0, 10);
  std::string time2 = timestamp2.substr(11, 8);

  if (time1 != time2)
  {
    std::vector<std::string> tokens1 = CSVReader::tokenise(time1, ':');
    std::vector<std::string> tokens2 = CSVReader::tokenise(time2, ':');
    int sec1 = std::stoi(tokens1[2]);
    int sec2 = std::stoi(tokens2[2]);
    int min1 = std::stoi(tokens1[1]);
    int min2 = std::stoi(tokens2[1]);
    int hour1 = std::stoi(tokens1[0]);
    int hour2 = std::stoi(tokens2[0]);

    interval += (hour1 - hour2) * 3600 + (min1 - min2) * 60 + (sec1 - sec2);
  }

  // if (day1 != day2)
  // {
  //   std::vector<std::string> tokens1 = CSVReader::tokenise(day1, '/');
  //   std::vector<std::string> tokens2 = CSVReader::tokenise(day2, '/');
  //   int day1 = std::stoi(tokens1[2]);
  //   int day2 = std::stoi(tokens2[2]);
  //   int month1 = std::stoi(tokens1[1]);
  //   int month2 = std::stoi(tokens2[1]);
  //   int year1 = std::stoi(tokens1[0]);
  //   int year2 = std::stoi(tokens2[0]);

  //   interval += (year1 - year2) * 3600 + (month1 - month2) * 60 + (day1 - day2) * 86400;
  // }

  return interval;
}

std::string OrderBookEntry::calcNextTimestamp(std::string timestamp, unsigned int interval)
{
  std::string day = timestamp.substr(0, 10);
  std::string time = timestamp.substr(11, 8);

  std::vector<std::string> tokens = CSVReader::tokenise(time, ':');
  int sec = std::stoi(tokens[2]);
  int min = std::stoi(tokens[1]);
  int hour = std::stoi(tokens[0]);
  int totalSeconds = hour * 3600 + min * 60 + sec + interval;

  std::string newHour = std::to_string((totalSeconds / 3600) % 24);
  if (newHour.length() < 2) newHour = "0" + newHour;
  std::string newMin = std::to_string((totalSeconds % 3600) / 60);
  if (newMin.length() < 2) newMin = "0" + newMin;
  std::string newSec = std::to_string(totalSeconds % 60);
  if (newSec.length() < 2) newSec = "0" + newSec;
  std::string newTime = newHour + ":" + newMin + ":" + newSec;

  return day + " " + newTime;
}

OrderBookType OrderBookEntry::stringToOrderBookType(std::string s)
{
  if (s == "ask")
  {
    return OrderBookType::ask;
  }
  if (s == "bid")
  {
    return OrderBookType::bid;
  }
  return OrderBookType::unknown;
}
