#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/projectile.h"

TEST_CASE("Point initialization", "[point]") {
    Point origin;

    REQUIRE( origin.x == 0 );
    REQUIRE( origin.y == 0 );

    Point point(3, 4);

    REQUIRE( point.x == 3 );
    REQUIRE( point.y == 4 );
}

TEST_CASE("Vector arithmetic", "[vector]") {
    SECTION("Magnitude") {
        REQUIRE( magnitude(0, 0) == 0.0 );
        REQUIRE( magnitude(3, 4) == 5.0 );
    }

    SECTION("Determinant") {
        REQUIRE( determinant(1, 2, 3, 4) == -2.0 );
        REQUIRE( determinant(3, 3, 3, 3) == 0.0 );
    }

    SECTION("Dot product") {
        Vector a(new Point, new Point(5, 1));
        Vector b(new Point, new Point(1, 5));

        REQUIRE( dot(a, b) == 10.0 );
    }

    SECTION("Normals and normalization") {
        Vector a(new Point, new Point(3, 4));
        auto norm = a.normal();

        REQUIRE( norm == Vector(new Point, new Point(-4, 3)) );
        double expected = 5.0 / 5.0;
        REQUIRE( norm.unit().mag == expected);
    }
}

TEST_CASE("Vector overlapping", "[vector]") {
    SECTION("General pass/no pass") {
        Vector a(new Point, new Point(5, 5));
        Vector b(new Point(5, 0), new Point(0, 5));

        REQUIRE( overlap(a, b) );

        Vector c(new Point, new Point(5, 5));
        Vector d(new Point(6, 6), new Point(6, 0));

        REQUIRE( !overlap(c, d) );
    }

    SECTION("Colinear special cases") {
        Vector a(new Point, new Point(5, 0));
        Vector b(new Point(3, 0), new Point(8, 0));
        Vector c(new Point(8, 0), new Point(3, 0));
        Vector d(new Point(2, 0), new Point(-3, 0));
        Vector e(new Point(-3, 0), new Point(2, 0));

        REQUIRE( overlap(a, b) );
        REQUIRE( overlap(a, c) );
        REQUIRE( overlap(d, a) );
        REQUIRE( overlap(e, a) );
    }
}

TEST_CASE("Constructing Polygons") {
    SECTION("init by vertices") {
        auto bottom_right = new Point(2, -2);
        auto bottom_left = new Point(-2, -2);
        auto top_left = new Point(-2, 2);
        auto top_right = new Point(2, 2);

        std::vector<Point*> verts = {bottom_right, bottom_left, top_left, top_right};

        Polygon square(verts);

        REQUIRE( *square.pos == *new Point );

        auto p0 = new Point(3, 0);
        auto p1 = new Point(0, 3);
        auto p2 = new Point(0, 6);
        auto p3 = new Point(3, 9);
        auto p4 = new Point(6, 9);
        auto p5 = new Point(9, 6);
        auto p6 = new Point(9, 3);
        auto p7 = new Point(6, 0);

        std::vector<Point*> oct_verts = {p0, p1, p2, p3, p4, p5, p6, p7};

        Polygon octagon(oct_verts);

        REQUIRE( *octagon.pos == *new Point(4.5, 4.5) );
    }

    SECTION("init by position") {
        Polygon square(new Point, 4, 4);

        REQUIRE( square.is_upright() );

        Polygon octagon(new Point, 8, 4);

        REQUIRE( octagon.is_upright() );

        Polygon triangle(new Point, 3, 4);

        REQUIRE( triangle.is_upright() );

        Polygon segment(new Point, 2, 3);

        REQUIRE( segment.is_upright() );
    }
}

TEST_CASE("Collision Detection") {
    SECTION("Polygon v Polygon") {
        auto p0 = new Point;
        auto p1 = new Point(1, 1);
        auto p2 = new Point(1, 0);

        std::vector<Point*> triplet = {p0, p1, p2};
        Polygon triangle(triplet);

        Polygon square(new Point(1.5, -0.5), 4, 2);

        REQUIRE( collision(triangle, square) );

        Polygon square2(new Point(5, 5));

        REQUIRE( !collision(square, square2) );
    }

    SECTION("Circle v Polygon") {
        Circle circle(new Point(3, 3), 3);
        Polygon square(new Point(4, 4), 4, 2);

        auto collided = collision(square, circle);

        REQUIRE( collided );

        auto p0 = new Point(2, 0);
        auto p1 = new Point(3, 3);
        auto p2 = new Point(4, 0);

        std::vector<Point*> triplet = {p0, p1, p2};
        Polygon triangle(triplet);

        REQUIRE( collision(triangle, circle) );

        Polygon square2(new Point(8, 8));

        REQUIRE( !collision(square2, circle) );
    }
}
