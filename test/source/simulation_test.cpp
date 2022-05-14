#include <catch2/catch.hpp>

#include "cimppy/simulation.hpp"
#include "cimppy/events.hpp"

TEST_CASE("Create simulation environment", "[simulation]")
{
    auto sim = cimppy::simulation();
    REQUIRE( sim.now() == 0 );
}


TEST_CASE("Negative run until", "[simulation]")
{
    auto sim = cimppy::simulation();
    REQUIRE_THROWS_AS(sim.run(-1), std::runtime_error);
}
