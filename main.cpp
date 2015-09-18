#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <functional>

TEST_CASE("bind test", "[misc]") {
  class Number {
  public:
    Number(int num): _num(num) {}
    int getNum() { return _num; }
  private:
    const int _num;
  };

  Number a(1);
  Number b(2);

  auto genericGetNum = std::bind(&Number::getNum, std::placeholders::_1);
  REQUIRE(genericGetNum(a) == 1);
  REQUIRE(genericGetNum(b) == 2);
}

TEST_CASE("bool compare test", "[misc]") {
  REQUIRE(true > false);
}

TEST_CASE("bool to int implicit conversion test", "[misc]") {
  const bool v1 = true, v2 = false, v3 = true;
  REQUIRE(v1 + v2 == 1);
  REQUIRE(2 * v1 == 2);
  REQUIRE(v1 + v3 == 2);
}

TEST_CASE("enum ordering test", "[misc]") {
  SECTION("default-valued enum") {
    enum class Values {FIRST, SECOND};
    REQUIRE(Values::FIRST < Values::SECOND);
    REQUIRE(Values::SECOND > Values::FIRST);
  }

  SECTION("custom-valued enums") {
    enum class Values {FIRST = 1, SECOND = -1};
    REQUIRE(Values::FIRST > Values::SECOND);
    REQUIRE(Values::SECOND < Values::FIRST);
  }
}
