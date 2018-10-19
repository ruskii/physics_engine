#ifndef PHYSICS_VECTORS_H
#define PHYSICS_VECTORS_H

#include <iostream>
#include <cmath>
#include "point.h"

double get_mag(double x, double y);

struct Vector {
    Vector() : tail(new Point), head(new Point), x_cmp(0), y_cmp(0), mag(0) {}
    Vector(Point *t, Point *h) : tail(t), head(h) {}
    ~Vector() = default;
    Point *tail;
    Point *head;
    double x_cmp = head->x - tail->x;
    double y_cmp = head->y - tail->y;
    double mag = get_mag(x_cmp, y_cmp);
};

Vector operator+(Vector& a, Vector& b);
Vector operator+=(Vector& a, Vector& b);
Vector operator-(Vector& a, Vector& b);
Vector operator-=(Vector& a, Vector& b);
Vector operator*(double scalar, Vector &a);
std::ostream& operator<<(std::ostream& os, Vector& vec);

#endif
