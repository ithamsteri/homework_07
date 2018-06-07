#define BOOST_TEST_MODULE Subscribers
#include <boost/test/unit_test.hpp>

#include "Subscribers.h"
#include <ostream>

BOOST_AUTO_TEST_CASE(BulkToOstream)
{
  std::vector<std::string> bulk{ "cmd1", "cmd2", "cmd3" };
  std::string result{ "bulk: cmd1, cmd2, cmd3\n" };

  std::ostringstream ostringstream;
  sendBulkToOstream(ostringstream, bulk);

  BOOST_REQUIRE_EQUAL(ostringstream.str(), result);
}

BOOST_AUTO_TEST_CASE(EmptyBulkToOstream)
{
  std::vector<std::string> emptyBulk;
  std::string result;

  std::ostringstream ostringstream;
  sendBulkToOstream(ostringstream, emptyBulk);

  BOOST_REQUIRE_EQUAL(ostringstream.str(), result);
}
