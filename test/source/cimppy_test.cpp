#include <string>

#include "cimppy/cimppy.hpp"

#include <catch2/catch.hpp>

TEST_CASE("Name is cimppy", "[library]")
{
  auto const exported = exported_class {};
  REQUIRE(std::string("cimppy") == exported.name());
}
