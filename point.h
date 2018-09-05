//
// Created by aapogodin on 7/22/18.
//

#ifndef PHYSICS_POINT_H
#define PHYSICS_POINT_H

/* Basic representation of a coordinate
   Default initialization is (0, 0)
*/
struct Point {
	Point() : x(0), y(0) {}
	Point(double x, double y) : x(x), y(y) {};
	double x, y;
};

#endif //PHYSICS_POINT_H
