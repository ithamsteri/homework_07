#define BOOST_TEST_MODULE Bulk
#include <boost/test/unit_test.hpp>

#include "BulkReader.h"
#include <ostream>
#include <sstream>
#include <vector>

std::string
bulkToString(const std::vector<std::string>& bulk)
{
  std::ostringstream ostringstream;

  for (auto iter = bulk.cbegin(); iter != bulk.cend(); ++iter) {
    if (iter == bulk.cbegin())
      ostringstream << *iter;
    else
      ostringstream << ' ' << *iter;
  }
  ostringstream << '\n';

  return ostringstream.str();
}

bool
bulkTest(size_t size, const std::string& commands, const std::string& expected)
{
  std::string result;
  std::istringstream istream(commands);

  BulkReader bulkReader(size, istream);
  bulkReader.subscribe([&result](const std::vector<std::string>& bulk) { result += bulkToString(bulk); });
  bulkReader.readCommands();

  return result == expected;
}

BOOST_AUTO_TEST_CASE(TreeSizeBulk)
{
  std::string commands = "cmd1 cmd2 cmd3";
  std::string expected = "cmd1 cmd2 cmd3\n";

  BOOST_REQUIRE(bulkTest(3, commands, expected));
}

BOOST_AUTO_TEST_CASE(OneSizeBulk)
{
  std::string commands = "cmd1 cmd2 cmd3";
  std::string expected = "cmd1\ncmd2\ncmd3\n";

  BOOST_REQUIRE(bulkTest(1, commands, expected));
}

BOOST_AUTO_TEST_CASE(BulkBlocks)
{
  std::vector<std::pair<std::string, std::string>> testData{
    std::make_pair("cmd1 cmd2 { cmd3 cmd4 cmd5 }", "cmd1 cmd2\ncmd3 cmd4 cmd5\n"),
    std::make_pair("cmd1 { cmd2 } cmd3", "cmd1\ncmd2\n"),
    std::make_pair("{ cmd1 } { cmd2 { cmd3 cmd4 } } cmd5 cmd6", "cmd1\ncmd2 cmd3 cmd4\n"),
    std::make_pair("{ cmd1 } { cmd2 cmd3 cmd4 cmd5 }", "cmd1\ncmd2 cmd3 cmd4 cmd5\n"),
    std::make_pair("{ } { cmd1 { { { cmd2 } } } }", "cmd1 cmd2\n"),
  };

  for (const auto pair : testData) {
    BOOST_REQUIRE(bulkTest(3, pair.first, pair.second));
  }
}

BOOST_AUTO_TEST_CASE(UnexpectedCloseBrace)
{
  std::string commands = "cmd1 { cmd3 } }";
  std::string expected = "exception";

  BOOST_REQUIRE_THROW(bulkTest(1, commands, expected), std::runtime_error);
}