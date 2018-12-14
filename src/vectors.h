#ifndef PHYSICS_VECTORS_H
#define PHYSICS_VECTORS_H

#include "point.h"

double magnitude(double x, double y);
double determinant(double a, double b, double c, double d);

struct Vector {
    Vector(Point *t = new Point, Point *h = new Point) : tail(t), head(h) {}
    ~Vector() = default;

    Point *tail;
    Point *head;
    double x_cmp = head->x - tail->x;
    double y_cmp = head->y - tail->y;
    double mag = magnitude(x_cmp, y_cmp);

    bool operator==(const Vector& other) const;
    Vector unit() const;
    Vector normal() const;
};

double dot(const Vector& a, const Vector& b);
bool colinear_intersection(const Point *p, const Point *q, const Point *r);
int point_orientation(const Point *p, const Point *q, const Point *r);
bool overlap(const Vector& a, const Vector& b);
Vector operator+(const Vector& a, const Vector& b);
Vector operator+=(Vector& a, const Vector& b);
Vector operator-(const Vector& a, const Vector& b);
Vector operator-=(Vector& a, const Vector& b);
Vector operator*(double scalar, const Vector &a);

#endif
