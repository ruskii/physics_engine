#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/rigidbody.h"


// TODO: create tests for all methods and functions, sections for different scenarios

TEST_CASE("Point initialization", "[point]") {
    Point origin;

    REQUIRE( origin.x == 0 );
    REQUIRE( origin.y == 0 );

    Point point(3, 4);

    REQUIRE( point.x == 3 );
    REQUIRE( point.y == 4 );
}

TEST_CASE("Vector arithmetic", "[vector]") {
    
    SECTION("Test magnitude") {
        for (int x = -5; x <= 5; x += 10) {
            for (int y = -5; y <= 5; y += 10) {
                Vector vec(new Point, new Point(x, y));
                REQUIRE(vec.get_mag() == sqrt(50));
            }
        }
    }

    Vector right(new Point, new Point(1, 0));
    Vector left(new Point, new Point(-1, 0));
    Vector up(new Point, new Point(0, 1));
    Vector down(new Point, new Point(0, -1));

    Vector right_2(new Point, new Point(2, 0));
    Vector left_2(new Point, new Point(-2, 0));
    Vector up_2(new Point, new Point(0, 2));

    Vector right_up(new Point, new Point(1, 1));
    Vector right_down(new Point, new Point(1, -1));
    Vector left_down(new Point, new Point(-1, -1));
    Vector zero_vec;

    SECTION("Test addition") {
        REQUIRE( right + left == zero_vec );
        REQUIRE( right + up == right_up );
        REQUIRE( right_up + left_down == zero_vec );
    }

    SECTION("Test subtraction") {
        REQUIRE( right - right == zero_vec );
        REQUIRE( right - left == right_2 );
        REQUIRE( right - up == right_down );
    }

    SECTION("Test scalar") {
        REQUIRE( 2 * right == right_2 );
        REQUIRE( 2 * up == up_2 );
        REQUIRE( -2 * down == up_2 );
    }

    SECTION("Test increment") {
        right += left;
        REQUIRE( right == zero_vec );

        up += up;
        REQUIRE( up == up_2 );
    }

    SECTION("Test decrement") {
        left -= right;
        REQUIRE( left == left_2 );

        up -= down;
        REQUIRE( up == up_2 );
    }
}

TEST_CASE("Position is verified", "[position]") {
    Rectangle rect(2, 2, 5, new Point(5, 5), new Vector, new Vector);

    REQUIRE( rect.pos->x == 5 );
    REQUIRE( rect.pos->y == 5 );

    Circle circ(3, 4, new Point(3, 4), new Vector, new Vector);

    REQUIRE( circ.pos->x == 3 );
    REQUIRE( circ.pos->y == 4 );
}

TEST_CASE("Velocity is verified", "[velocity]") {
    Rectangle rect(2, 2, 5, new Point, new Vector(new Point, new Point(3, 4)), new Vector);

    REQUIRE( rect.vel->x_cmp == 3 );
    REQUIRE( rect.vel->y_cmp == 4 );
}

TEST_CASE("Collision Detection") {

    SECTION("Rectangle Rectangle") {
        Rectangle a(4, 4, 1, new Point, new Vector, new Vector);
        Rectangle b(3, 3, 1, new Point(3, 0), new Vector, new Vector);
        Rectangle c(3, 3, 1, new Point(-1, 3), new Vector, new Vector);

        REQUIRE( a.collides_with(b) );
        REQUIRE( a.collides_with(c) );
        REQUIRE( !b.collides_with(c) );
    }

    SECTION("Rectangle Circle") {
        Rectangle r1(6, 6, 1, new Point, new Vector, new Vector);
        Circle c1(4, 1, new Point(4, 0), new Vector, new Vector);
        Circle c2(10, 1, new Point(12, 12), new Vector, new Vector);

        REQUIRE( r1.collides_with(c1) );
        REQUIRE( c1.collides_with(r1) );
        REQUIRE( !r1.collides_with(c2) );
        REQUIRE( !c2.collides_with(r1) );
    }

    SECTION("Circle Circle") {
        Circle a(4, 1, new Point, new Vector, new Vector);
        Circle b(2, 1, new Point(5, 0), new Vector, new Vector);
        Circle c(2, 1, new Point(0, 5), new Vector, new Vector);

        REQUIRE( a.collides_with(b) );
        REQUIRE( a.collides_with(c) );
        REQUIRE( !b.collides_with(c) );
    }
}

TEST_CASE("Applying force", "[force]") {
    Rectangle rect(4, 2, 3, new Point, new Vector, new Vector);
    Vector f1(new Point, new Point(5, 0));
    Vector f2(new Point, new Point(-3, 0));

    apply_force(rect, f1);
    apply_force(rect, f2);

    auto netf = rect.get_netforce();

    REQUIRE( netf.x_cmp == 2 );
    REQUIRE( netf.y_cmp == 0 );
}

