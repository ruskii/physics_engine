#ifndef PHYSICS_POLYGON_H
#define PHYSICS_POLYGON_H

#include <vector>
#include "polygon.h"

struct RigidBody {
    explicit RigidBody(Polygon& poly, double av = 0, double tq = 0, \
        double m = 1, Vector *v = new Vector, Vector *a = new Vector) : \
        shape(poly), mass(m), angular_vel(av), torque(tq), vel(v), accel(a) {}

    Polygon shape;
    double mass;
    double angular_vel;
    double torque;
    Vector *vel;
    Vector *accel;
    Vector net_force;
    std::vector<Vector> forces; // all forces acting on rigidbody

    void update_accel();    // update acceleration based on netforce
    void sum_forces();  // sum all forces acting on rigidbody to obtain netforce
};

#endif