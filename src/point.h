#ifndef PHYSICS_POINT_H
#define PHYSICS_POINT_H

struct Point {
    explicit Point(double x = 0, double y = 0) : x(x), y(y) {};
    double x, y;

    bool operator==(const Point& other) const {return x == other.x and y == other.y;}
};

inline Point* midpoint(const Point& a, const Point& b) {return new Point((a.x + b.x) / 2, (a.y + b.y) / 2);}

#endif
