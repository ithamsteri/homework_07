#include "BulkReader.h"
#include "Subscribers.h"
#include <iostream>

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
