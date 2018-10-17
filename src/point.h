#ifndef PHYSICS_POINT_H
#define PHYSICS_POINT_H

struct Point {
	Point() : x(0), y(0) {}
	Point(double x, double y) : x(x), y(y) {};
	double x, y;
};

#endif
