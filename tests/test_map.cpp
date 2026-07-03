#include <map.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("insert works") {
    stl::map<int, std::string> m;
    m.insert(1, "one");
    REQUIRE(m.size() == 1);
}

TEST_CASE("find works") {
    stl::map<int, std::string> m;
    m.insert(1, "one");
    m.insert(2, "two");

    REQUIRE(m.find(2));
}

TEST_CASE("find not present works") {
    stl::map<int, std::string> m;
    m.insert(1, "one");
    m.insert(2, "two");

    REQUIRE_FALSE(m.find(3));
}

TEST_CASE("operator[] insert") {
    stl::map<int, std::string> m;
    m[5] = "five";

    REQUIRE(*(m.find(5)) == "five");
    REQUIRE(m.size() == 1);
}

TEST_CASE("operator[] already present") {
    stl::map<int, std::string> m;
    m.insert(5, "five");

    REQUIRE(*(m.find(5)) == "five");
    m[5] = "four";
    REQUIRE(*(m.find(5)) == "four");
    REQUIRE(m.size() == 1);
}