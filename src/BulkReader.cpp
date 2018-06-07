#include "BulkReader.h"

void
BulkReader::readCommands() const
{
  std::vector<std::string> bulkBuffer;
  bulkBuffer.reserve(bulk_size_);

  std::string command;
  size_t depth = 0;

  while (!istream_.eof()) {
    istream_ >> command;

    if (command == "{") {
      if (depth == 0 && !bulkBuffer.empty()) {
        notify(bulkBuffer);
        bulkBuffer.resize(0);
      }
      ++depth;
    } else if (command == "}") {
      if (depth > 0) {
        --depth;
        if (depth == 0 && !bulkBuffer.empty()) {
          notify(bulkBuffer);
          bulkBuffer.resize(0);
        }
      } else {
        throw std::runtime_error("Unexpected symbol '}' in input stream.");
      }
    } else {
      bulkBuffer.emplace_back(command);
      if (depth == 0 && bulkBuffer.size() == bulk_size_) {
        notify(bulkBuffer);
        bulkBuffer.resize(0);
      }
    }
  }
}
