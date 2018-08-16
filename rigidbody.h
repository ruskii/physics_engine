#pragma once
#include <iostream>
#include <utility>
#include <unistd.h>
#include <cmath>
#include <vector>
#include "vectors.h"
#include "point.h"
#include <typeinfo>

// To detect collisions by defining rigid bodies for 2D shapes by using "Is-A" relationship

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
    friend ostream& operator<<(ostream& os, RigidBody& rbd);
    void set_vel(Vector *v);
    void set_accel();
    Vector get_netf();
    virtual bool collides_with(Rectangle *r) = 0;
    virtual bool collides_with(Circle *c) = 0;
};

/* Rigid body of a 2D box (rectangle, square)
   Defined by a the length and width and two points, min and max */
struct Rectangle : public RigidBody {
    Rectangle(): RigidBody(), length(1), width (1) {set_corners();};
    Rectangle(double l, double w, double m, Point *p, Vector *v, Vector *a): RigidBody(m, p, v, a), length(l), width(w) {set_corners();};

    double length;
    double width;
    Point *min;     // Top right corner
    Point *max;     // Bottom left corner
    void set_corners();
    bool collides_with(Rectangle *r) override;
    bool collides_with(Circle *c) override;
};

/* Rigid body of a 2D circle
   Defined by a point, from vectors.h, and a radius */
struct Circle : public RigidBody {
    Circle(): RigidBody(), radius(1) {}
    Circle(double r, double m, Point *p, Vector *v, Vector *a): RigidBody(m, p, v, a), radius(r) {}
    double radius;
    bool collides_with(Rectangle *r) override;
    bool collides_with(Circle *c) override;
};

void apply_force(RigidBody& rb, Vector f) {
    rb.forces.push_back(f);
    rb.set_accel();
}

void move(RigidBody& rb, float dt) {
    rb.vel->x_cmp += rb.accel->x_cmp * dt;
    rb.vel->y_cmp += rb.accel->y_cmp * dt;
    rb.vel->mag = get_mag(rb.vel->x_cmp, rb.vel->y_cmp);
    rb.pos->x += rb.vel->x_cmp * dt;
    rb.pos->y += rb.vel->y_cmp * dt;
}

bool scan_collision(RigidBody *a, RigidBody *b) {
    auto b_rect = dynamic_cast<Rectangle*>(b);

    if (b_rect)
        return a->collides_with(b_rect);
    else {
        auto b_circ = dynamic_cast<Circle*>(b);
        return a->collides_with(b_circ);
    }
}

ostream& operator<<(ostream& os, RigidBody& rbd) {
        string op = "pos[x: " + to_string(rbd.pos->x) + ", y: " + to_string(rbd.pos->y) + "]\nvel[x: " + \
        to_string(rbd.vel->x_cmp) + ", y: " + to_string(rbd.vel->y_cmp) + ", abs: " + to_string(rbd.vel->mag) + "]";
        os << op << endl;
        return os;
}
