#ifndef BULK_BULK_H
#define BULK_BULK_H

#include <cstddef>
#include <exception>
#include <functional>
#include <iostream>
#include <vector>

/// Reader of bulks from input streams and send them to subscribers.
class BulkReader
{
public:
  /// Constructor of BulkReader
  /// @param bulk_size count of commands in bulk
  /// @param istream input stream for reading commands
  BulkReader(size_t bulk_size, std::istream& istream = std::cin)
    : bulk_size_{ bulk_size }
    , istream_{ istream }
  {}

  /// Subscription to received data from BulkReader.
  /// @param function reference on `std::function` for receiving bulks
  void subscribe(const std::function<void(const std::vector<std::string>&)>& function) { subscribers_.push_back(function); }

  /// Start reading commands from input stream and send bulks to subscribers.
  /// @throw `std::runtime` if get unexpected '}' in input stream
  void readCommands() const;

private:
  std::vector<std::function<void(const std::vector<std::string>&)>> subscribers_;
  std::istream& istream_;
  size_t bulk_size_;

  /// Send bulk to all subscribers
  /// @param bulk bulk for subscribers
  void notify (const std::vector<std::string>& bulk) const
  {
    for (const auto& subscriber : subscribers_) {
      subscriber(bulk);
    }
  }
};

#endif // BULK_BULK_H
