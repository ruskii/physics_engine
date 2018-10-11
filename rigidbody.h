#pragma once
#include <iostream>
#include <utility>
#include <unistd.h>
#include <cmath>
#include <vector>
#include "vectors.h"
#include "point.h"
#include <typeinfo>

struct Rectangle;
struct Circle;

struct RigidBody{
    RigidBody() : mass(1), pos(new Point), vel(new Vector), accel(new Vector) {}
    RigidBody(double m, Point *p, Vector *v, Vector *a) : mass(m), pos(p), vel(v), accel(a) {}
    double mass;
    Point *pos;
    Vector *vel;
    Vector *accel;
    vector<Vector> forces;          // stores all forces acting on particle
    void set_vel(Vector *v);
    void set_accel();
    Vector get_netf();
    virtual bool collides_with(Rectangle *r) = 0;
    virtual bool collides_with(Circle *c) = 0;
    friend ostream& operator<<(ostream& os, RigidBody& rbd);
};

struct Rectangle : public RigidBody {
    Rectangle(): RigidBody(), length(1), width (1) {set_corners();}
    Rectangle(double l, double w, double m, Point *p, Vector *v, Vector *a): RigidBody(m, p, v, a), length(l), width(w) {set_corners();}

    double length;
    double width;
    Point *min;     // Top right corner
    Point *max;     // Bottom left corner
    void set_corners();
    bool collides_with(Rectangle *r) override;
    bool collides_with(Circle *c) override;
};

struct Circle : public RigidBody {
    Circle(): RigidBody(), radius(1) {}
    Circle(double r, double m, Point *p, Vector *v, Vector *a): RigidBody(m, p, v, a), radius(r) {}
    double radius;
    bool collides_with(Rectangle *r) override;
    bool collides_with(Circle *c) override;
};

