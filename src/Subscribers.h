#ifndef BULK_SUBCRIBERS_H
#define BULK_SUBCRIBERS_H

#include <ostream>
#include <vector>

void
sendBulkToOstream(std::ostream& ostream, const std::vector<std::string>& bulk);

void
bulkToLogFile(const std::vector<std::string>& bulk);

#endif // BULK_SUBCRIBERS_H
