#ifndef PHYSICS_POLYGON_H
#define PHYSICS_POLYGON_H

#include <vector>
#include "polygon.h"

struct RigidBody {
    explicit RigidBody(Polygon& poly, Point *p = nullptr, double ort=0, double av=0, double tq=0) : \
        shape(poly), pos(p), orientation(ort), angular_vel(av), torque(tq) {}

    Point *pos;
    Polygon shape;
    double orientation;     // radians
    double angular_vel;
    double torque;
};

struct Projectile : RigidBody {
    explicit Projectile(Polygon& poly, Point *p, double ort, double av, double tq, \
        double m = 1, Vector *v = new Vector, Vector *a = new Vector) : \
        RigidBody(poly, p, ort, av, tq), mass(m), vel(v), accel(a) {}

    double mass;
    Vector *vel;
    Vector *accel;
    Vector net_force;
    std::vector<Vector> forces;

    void update_accel();
    void sum_forces();
};

#endif