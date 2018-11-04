#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/rigidbody.h"

/*
TODO:
    - create tests for all methods and functions, sections for different scenarios
    - look into user generated tests with IO redirection
*/   

TEST_CASE("Position is verified", "[position]") {
    Rectangle rect(2, 2, 5, new Point(5, 5), new Vector, new Vector);

    REQUIRE(rect.pos->x == 5);
    REQUIRE(rect.pos->y == 5);

    Circle circ(3, 4, new Point(3, 4), new Vector, new Vector);

    REQUIRE(circ.pos->x == 3);
    REQUIRE(circ.pos->y == 4);
}

TEST_CASE("Velocity is verified", "[velocity]") {
    Rectangle rect(2, 2, 5, new Point, new Vector(new Point, new Point(3, 4)), new Vector);

    REQUIRE(rect.vel->x_cmp == 3);
    REQUIRE(rect.vel->y_cmp == 4);
}

TEST_CASE("Applying force", "[force]") {
    Rectangle rect(4, 2, 3, new Point, new Vector, new Vector);
    Vector f1(new Point, new Point(5, 0));
    Vector f2(new Point, new Point(-3, 0));

    apply_force(rect, f1);
    apply_force(rect, f2);

    auto netf = rect.get_netforce();

    REQUIRE(netf.x_cmp == 2);
    REQUIRE(netf.y_cmp == 0);    
}
