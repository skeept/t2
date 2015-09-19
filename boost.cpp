#include "catch.hpp"
#include <boost/icl/interval.hpp>
#include <boost/icl/interval_set.hpp>
#include <boost/icl/separate_interval_set.hpp>
#include <boost/optional.hpp>

TEST_CASE("interval tests", "[boost]") {
  using namespace boost::icl;

  SECTION("closed intervals") {
    auto ival = interval<int>::closed(1, 3);
    REQUIRE(ival.lower() == 1);
    REQUIRE(ival.upper() == 3);
  }

  SECTION("open intervals") {
    auto ival = interval<int>::open(1, 3);
    REQUIRE(ival.lower() == 1);
    REQUIRE(ival.upper() == 3);
  }

  SECTION("interval sets") {
    //interval sets contain exactly one interval at any time.
    //interval bounds expand based on addition of new intervals.
    auto iSet = interval_set<int>{};
    iSet += interval<int>::closed(1, 3);
    iSet += interval<int>::closed(2, 5); //upper bound expands to 5
    iSet += interval<int>::closed(0, 4); //lower bound expands to 0
    REQUIRE(contains(iSet, 0));
    REQUIRE(contains(iSet, 3));
    REQUIRE(contains(iSet, 5));
    REQUIRE_FALSE(contains(iSet, 7));
  }

  SECTION("separate interval sets") {
    auto siSet = separate_interval_set<int>{};
    siSet += interval<int>::closed(1, 3); //is now {(1,3)}
    siSet += interval<int>::closed(9, 10); //is now {(1,3), (9,10)}
    siSet += interval<int>::closed(2, 5); //is now {(1,5), (9,10)}
 
    REQUIRE(contains(siSet, 4));
    REQUIRE_FALSE(contains(siSet, 7));
    REQUIRE_FALSE(contains(siSet, 8));
    REQUIRE(contains(siSet, 9));

    REQUIRE(intersects(siSet, interval<int>::closed(2, 7)));
    REQUIRE_FALSE(intersects(siSet, interval<int>::closed(11, 12)));
    REQUIRE(intersects(siSet, interval<int>::closed(5, 6)));
    REQUIRE(intersects(siSet, interval<int>::closed(5, 9)));
    REQUIRE_FALSE(intersects(siSet, interval<int>::closed(7, 8)));
    REQUIRE(intersects(siSet, interval<int>::closed(7, 9)));
  }
}

TEST_CASE("optional test", "[boost]") {
  SECTION("optional construction") {
    auto optInt = boost::optional<int>{};
    REQUIRE_FALSE(optInt.is_initialized());
    optInt = 1;
    REQUIRE(optInt.is_initialized());
    REQUIRE(optInt.get() == 1);
  }

  SECTION("optional returning function") {
    auto positivePart = [](int num)->boost::optional<int> {
      return num > 0 ? num : boost::optional<int>{};
    };

    auto optVal = positivePart(5);
    REQUIRE(optVal.is_initialized());
    REQUIRE(optVal.get() == 5);
    REQUIRE_FALSE(positivePart(-5).is_initialized());
  }
}
