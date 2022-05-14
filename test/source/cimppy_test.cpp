#include <string>
#include <catch2/catch.hpp>

#include "cimppy/cimppy.hpp"

TEST_CASE("Name is cimppy", "[library]")
{
  auto const exported = exported_class {};
  REQUIRE(std::string("cimppy") == exported.name());
}
