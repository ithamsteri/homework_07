#include "Subscribers.h"
#include <chrono>
#include <fstream>
#include <iostream>

void
sendBulkToOstream(std::ostream& ostream, const std::vector<std::string>& bulk)
{
  ostream << "bulk: ";
  for (auto iter = bulk.cbegin(); iter != bulk.cend(); ++iter) {
    if (iter != bulk.cbegin())
      ostream << ", " << *iter;
    else
      ostream << *iter;
  }
  ostream << std::endl;
}

void
bulkToLogFile(const std::vector<std::string>& bulk)
{
  std::string timestamp = std::to_string(
    std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());
  std::string filename = "bulk" + timestamp + ".log";

  std::fstream fstream(filename, std::ios::out | std::ios::app);
  if (!fstream.is_open()) {
    std::cerr << "Error opening file: " << filename << std::endl;
    return;
  }

  sendBulkToOstream(fstream, bulk);
}