#pragma once
#include <iostream>
#include <utility>
#include <unistd.h>
#include <cmath>
#include <vector>
#include "vectors.h"
#include "point.h"
#include <typeinfo>

/*
This will function as a base for all of our shapes.
Rigidbody serves as an abstract class for Circle and Rectangle, making it easier to 
detect collisions between the two different objects.

Also includes some standalone movement functions and a function for determining
collision type - scan_collision(RigidBody& a, RigidBody& b)
*/

struct Rectangle;
struct Circle;

// includes all the necessary attributes and virtual functions for our shapes
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
    virtual bool collides_with(Rectangle *r) = 0;	// pure virtual functions are overridden in Rectangle and Circle
    virtual bool collides_with(Circle *c) = 0;
};

/* Rigid body of a 2D box
   Must call base struct constructor RigidBody
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
   Must call base struct constructor RigidBody
   Defined by a point, from vectors.h, and a radius */
struct Circle : public RigidBody {
    Circle(): RigidBody(), radius(1) {}
    Circle(double r, double m, Point *p, Vector *v, Vector *a): RigidBody(m, p, v, a), radius(r) {}
    double radius;
    bool collides_with(Rectangle *r) override;
    bool collides_with(Circle *c) override;
};

/* Takes a force and applies it to given RigidBody
   Force is added to RigidBody's container of forces
   Net acceleration is recalculated */
void apply_force(RigidBody& rb, Vector f) {
    rb.forces.push_back(f);
    rb.set_accel();
}

/* Update velocity components and magnitude based off of acceleration
   Update position off of velocity components */
void move(RigidBody& rb, float dt) {
    rb.vel->x_cmp += rb.accel->x_cmp * dt;
    rb.vel->y_cmp += rb.accel->y_cmp * dt;
    rb.vel->mag = get_mag(rb.vel->x_cmp, rb.vel->y_cmp);
    rb.pos->x += rb.vel->x_cmp * dt;
    rb.pos->y += rb.vel->y_cmp * dt;
}

/* Determine collision type by dynamically casting RigidBody b to Rectangle
   If b is not a Rectangle, dynamic cast will return a nullptr, which we then dynamic cast to a circle
   If b is a rectangle, call rectangle collision function by referencing a, which can be a circle or a rectangle */
bool scan_collision(RigidBody *a, RigidBody *b) {
    auto b_rect = dynamic_cast<Rectangle*>(b);

    if (b_rect)
        return a->collides_with(b_rect);
    else {
        auto b_circ = dynamic_cast<Circle*>(b);
        return a->collides_with(b_circ);
    }
}

/* Output RigidBody position and velocity components
*/
ostream& operator<<(ostream& os, RigidBody& rbd) {
        string op = "pos[x: " + to_string(rbd.pos->x) + ", y: " + to_string(rbd.pos->y) + "]\nvel[x: " + \
        to_string(rbd.vel->x_cmp) + ", y: " + to_string(rbd.vel->y_cmp) + ", abs: " + to_string(rbd.vel->mag) + "]";
        os << op << endl;
        return os;
}
