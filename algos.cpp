#include "catch.hpp"
#include <functional>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

namespace {
  auto nums = std::vector<int> { 1, 2, 3, 4, 5, 6 };
  auto evens = std::vector<int> { 2, 4, 6 };
  auto odds = std::vector<int> { 1, 3, 5 };
  auto isOdd = [](const int num) { return num%2 != 0; };
}

TEST_CASE("accumulate test", "[algos]") {
  SECTION("string concatenation") {
    auto sv = std::vector<std::string>{ "aa", "bb", "cc" };
    auto result = std::accumulate(sv.begin(), sv.end(), std::string(""));
    REQUIRE("aabbcc" == result);
  }

  SECTION("vector sum") {
    auto res = std::accumulate(nums.begin(), nums.end(), 0, [](int acc, int val) {
      return acc + 2 * val;
    });
    REQUIRE(res == 42);
  }
}

TEST_CASE("copy_if test", "[algos]") {
  auto nums = std::vector<int> { 1, 2, 3, 4, 5, 6 };
  auto res = std::vector<int>{};
  std::copy_if(nums.begin(), nums.end(), std::back_inserter(res), isOdd);
  REQUIRE(res == odds);
}

TEST_CASE("erase test", "[algos]") {
  auto numsCopy = std::vector<int>{ nums };
  numsCopy.erase(numsCopy.begin() + 1, numsCopy.end());
  REQUIRE(numsCopy == std::vector<int>{1});
}

TEST_CASE("backward find_if test", "[algos]") {
  SECTION("successful search case") {
    const auto it = std::find_if(nums.rbegin(), nums.rend(), [](int n) { return n%2 == 0; });
    REQUIRE(it == nums.rbegin());
  }

  SECTION("failed search case") {
    const auto it = std::find_if(nums.rbegin(), nums.rend(), [](int n) { return n%2 < 0; });
    REQUIRE(it == nums.rend());
  }
}

TEST_CASE("max of range test", "[algos]") {
  const auto val = std::max({1, 2, 3, 4, 5});
  REQUIRE(val == 5);
}

TEST_CASE("move to empty vector test", "[algos]") {
  auto copy1 = std::vector<int>{ nums };
  auto copy2 = std::vector<int>{};
  copy2 = std::move(copy1);
  REQUIRE(copy2 == nums);
}

TEST_CASE("move to non-empty vector test", "[algos]") {
  auto copy1 = std::vector<int>{ nums };
  auto copy2 = std::vector<int>{ 0, 0 };
  auto res = std::vector<int>{ 0, 0, 1, 2, 3, 4, 5, 6 }; 
  std::move(copy1.begin(), copy1.end(), std::back_inserter(copy2));
  REQUIRE(copy2 == res);
}

TEST_CASE("remove_if test", "[algos]") {
  auto numsCopy = std::vector<int>{ nums };
  numsCopy.erase(std::remove_if(numsCopy.begin(), numsCopy.end(), isOdd), numsCopy.end());
  REQUIRE(numsCopy == evens);
}

TEST_CASE("set copy_if test", "[algos]") {
  auto set1 = std::set<int>{ 1, 2, 4, 6 };
  auto res = std::set<int>(nums.begin(), nums.end());
  std::copy_if(nums.begin(), nums.end(), std::inserter(set1, set1.begin()), isOdd);
  REQUIRE(set1 == res);
}

TEST_CASE("set difference test", "[algos]") {
  auto set1 = std::set<int>{ 3, 2, 1 };
  auto set2 = std::set<int>{ 2, 4, 5, 3 };
  auto setDiff = std::vector<int>(set1.size() + set2.size());
  auto it = set_difference(set2.begin(), set2.end(), set1.begin(), set1.end(), setDiff.begin());
  setDiff.resize(it - setDiff.begin());
  auto res = std::vector<int>{ 4, 5 };
  REQUIRE(setDiff == res);
}

TEST_CASE("set insertion test", "[algos]") {
  auto set1 = std::set<int>{ 1, 2, 4 };
  auto res = std::set<int>{ nums.begin(), nums.end() };
  set1.insert(nums.begin(), nums.end());
  REQUIRE(set1 == res);
}

TEST_CASE("set intersection test", "[algos]") {
  auto set1 = std::set<int>{ 3, 2, 1 };
  auto set2 = std::set<int>{ 2, 4, 5, 3 };
  auto inter = std::vector<int>(set1.size() + set2.size());
  auto it = set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), inter.begin());
  inter.resize(it - inter.begin());
  std::vector<int> res = { 2, 3 };
  REQUIRE(inter == res);
}

TEST_CASE("sort test", "[algos]") {
  auto numsCopy = std::vector<int>{nums};
  auto orderedRes = std::vector<int>{ 1, 3, 5, 2, 4, 6 };
  auto comparator = [](int i, int j) {
    const bool iOdd = i%2 != 0;
    const bool jOdd = j%2 != 0;

    if(iOdd) {
      if(jOdd)
        return false;
      return true;
    }

    return false;
  };
  std::sort(numsCopy.begin(), numsCopy.end(), comparator);
  REQUIRE(numsCopy == orderedRes);
}

TEST_CASE("stable partition test", "[algos]") {
  auto numsCopy = std::vector<int>{nums};
  auto oddNums = std::vector<int>{};
  auto res = std::vector<int>{ 1, 3, 5, 2, 4, 6 };
  auto it = std::stable_partition(numsCopy.begin(), numsCopy.end(), isOdd);
  oddNums.insert(oddNums.end(), numsCopy.begin(), it);
  REQUIRE(numsCopy == res);
  REQUIRE(oddNums == odds);
}

TEST_CASE("transform test", "[algos]") {
  auto twiceNums = std::vector<int>(nums.size());
  auto res = std::vector<int>{ 2, 4, 6, 8, 10, 12 };
  std::transform(nums.begin(), nums.end(), twiceNums.begin(), [](int a) { return a*2; });
  REQUIRE(twiceNums == res);
}

TEST_CASE("unordered map test", "[algos]") {
  auto someMap = std::unordered_map<int, std::vector<char>>{};

  someMap[1].push_back('a');
  REQUIRE(someMap.count(1) == 1);

  someMap[1].push_back('b');
  REQUIRE(someMap[1].size() == 2);

  someMap[2].push_back('c');
  REQUIRE(someMap.count(2) == 1);
  REQUIRE(someMap[2].size() == 1);
  REQUIRE(someMap.size() == 2);
}
