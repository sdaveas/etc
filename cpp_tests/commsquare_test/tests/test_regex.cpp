#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../Regex.hpp"
#include <catch2/catch.hpp>

TEST_CASE("Regex") {
  SECTION("Replace") {
    constexpr const char *buffer = "This is no other than a test buffer.";
    Regex rgx("a|e|i|o|u");
    auto result = rgx.replace(buffer, "[$&]");
    constexpr const char *res_buffer =
        "Th[i]s [i]s n[o] [o]th[e]r th[a]n [a] t[e]st b[u]ff[e]r.";
    REQUIRE(memcmp(result.data(), res_buffer, result.length()) == 0);
  }
}
