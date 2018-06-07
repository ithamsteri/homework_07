#include "BulkReader.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <iterator>

void
sendBulkToOstream(std::ostream& ostream, const BulkReader::Bulk& bulk)
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
bulkToLogFile(const BulkReader::Bulk& bulk)
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

int
main(int argc, char* argv[])
{
  if (argc < 2) {
    std::cerr << "Use: " << argv[0] << " <bulk_size>\n";
    return EXIT_FAILURE;
  }

  int bulk_size = std::atoi(argv[1]);
  if (bulk_size <= 0) {
    std::cerr << "Error: Not correct bulk size.\n";
    return EXIT_FAILURE;
  }

  BulkReader reader(static_cast<size_t>(bulk_size));
  reader.subscribe([](const BulkReader::Bulk& bulk) { sendBulkToOstream(std::cout, bulk); });
  reader.subscribe(bulkToLogFile);

  try {
    reader.readCommands();
  } catch (std::runtime_error& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return 0;
}
