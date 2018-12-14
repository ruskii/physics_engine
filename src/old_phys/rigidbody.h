#ifndef PHYSICS_RIGIDBODY_H
#define PHYSICS_RIGIDBODY_H

#include <vector>
#include "vectors.h"

struct Rectangle;
struct Circle;

struct RigidBody {
    explicit RigidBody(double m = 1, \
        Point *p = new Point, Vector *v = new Vector, Vector *a = new Vector) :  \
        mass(m), pos(p), vel(v), accel(a) {}

    double mass;
    Point *pos;
    Vector *vel;
    Vector *accel;
    Vector net_force;
    std::vector<Vector> forces;          // stores all forces acting on particle

    virtual void set_pos(Point *p);
    void set_vel(Vector *v);
    void set_accel(Vector *a);
    void update_accel();
    void sum_forces();
    Vector get_netforce() const;
    virtual bool collides_with(const Rectangle &r) const = 0;
    virtual bool collides_with(const Circle &c) const = 0;
};

struct Rectangle : RigidBody {
    explicit Rectangle(double l = 1, double w = 1, double m = 1, \
        Point *p = new Point, Vector *v = new Vector, Vector *a = new Vector): \
        RigidBody(m, p, v, a), length(l), width(w) {set_corners();}

    double length;
    double width;
    Point *min;     // Top right corner
    Point *max;     // Bottom left corner

    void set_corners();
    void set_pos(Point *p) override;
    bool collides_with(const Rectangle &r) const override;
    bool collides_with(const Circle &c) const override;
};

struct Circle : RigidBody {
    explicit Circle(double r = 1, double m = 1, \
        Point *p = new Point, Vector *v = new Vector, Vector *a = new Vector): \
        RigidBody(m, p, v, a), radius(r) {}

    double radius;

    bool collides_with(const Rectangle &r) const override;
    bool collides_with(const Circle &c) const override;
};

void apply_force(RigidBody& rb, const Vector &f);

void move(RigidBody& rb, float dt);

bool scan_collision(const RigidBody &a, RigidBody &b);

#endif
