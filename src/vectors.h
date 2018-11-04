#ifndef PHYSICS_VECTORS_H
#define PHYSICS_VECTORS_H

#include "point.h"

double magnitude(double x, double y);

struct Vector {
    Vector() : tail(new Point), head(new Point), x_cmp(0), y_cmp(0), mag(0) {}
    Vector(Point *t, Point *h) : tail(t), head(h) {}
    ~Vector() = default;

    Point *tail;
    Point *head;
    double x_cmp = head->x - tail->x;
    double y_cmp = head->y - tail->y;
    double mag = magnitude(x_cmp, y_cmp);

    double get_mag() const;
    bool operator==(const Vector& other) const;
};

Vector operator+(const Vector& a, const Vector& b);
Vector operator+=(Vector& a, const Vector& b);      // make a const or non-const??
Vector operator-(const Vector& a, const Vector& b);
Vector operator-=(Vector& a, const Vector& b);
Vector operator*(double scalar, const Vector &a);
std::ostream& operator<<(std::ostream& os, const Vector& vec);

#endif
