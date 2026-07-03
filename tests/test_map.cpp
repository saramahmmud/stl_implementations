#include <map.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("insert works") {
    stl::map<int, std::string> m;
    m.insert(1, "one");
    REQUIRE(m.size() == 1);
}