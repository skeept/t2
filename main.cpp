#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Trying out catch tests", "[catch-test-test]") {
  REQUIRE(1==2);
  REQUIRE(1 == 1);
}
