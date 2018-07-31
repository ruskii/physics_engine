#include <iostream>
#include <utility>
#include <unistd.h>
#include <cmath>
#include <vector>
#include "vectors.h"
#include "point.h"

// To detect collisions by defining rigid bodies for 2D shapes by using "Is-A" relationship

struct RigidBody{
    RigidBody() : mass(1), pos(new Point), vel(new Vector), accel(new Vector) {}
    RigidBody(double m, Point *p, Vector *v, Vector *a) : mass(m), pos(p), vel(v), accel(a) {}
    double mass;
    Point *pos;
    Vector *vel;
    Vector *accel;
    vector<Vector> forces;          // stores all forces acting on particle
    friend ostream& operator<<(ostream& os, RigidBody& rbd);

    void set_vel(Vector *v) {vel = v;}

    void set_accel(Vector f) {  // returns acceleration from applying force to particle
        auto net_force = get_netf();
        auto acc_head = new Point(net_force.x_cmp / mass, net_force.y_cmp / mass);
        accel = new Vector(net_force.tail, acc_head);
    }

    Vector get_netf() {
        if (forces.empty()) return {new Point, new Point};

        auto netf = forces[0];
        for (int i = 1; i < forces.size(); i++)
            netf = netf + forces[i];
        return netf;
    }

    bool collides_with(RigidBody& B) {
        return pos->x == B.pos->x and pos->y == B.pos->y;
    }
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

    void set_corners() {
        min = new Point(RigidBody::pos->x - length / 2, RigidBody::pos->y - width / 2);
        max = new Point(RigidBody::pos->x + length / 2, RigidBody::pos->y + width / 2);
    }

    bool collides_with(Rectangle& B) {
        set_corners();
        B.set_corners();
        if (max->x < B.min->x or min->x > B.max->x)
            return false;
        return !(max->y < B.min->y or min->y > B.max->y);
    }
/*
    bool collides_with(Circle& B) {     // TODO: remove code duplication with CvR collisions
        Rectangle aabb(2 * B.radius, 2 * B.radius, B.mass, B.pos, B.vel, B.accel);

        if (!collides_with(aabb)) return false;

        if (B.pos->x < max->x and B.pos->x > min->x)
            return true;
        if (B.pos->y < max->y and B.pos->y > min->y)
            return true;

        vector<Point*> corners = {min, max, new Point(min->x, max->y), new Point(max->x, min->y)};

        for (auto corner : corners) {
            double y = pow(pos->x - corner->x, 2);
            double z = pow(pos->y - corner->y, 2);
            if (B.radius > (y + z))
                return true;
        }
    }
    */
};

/* Rigid body of a 2D circle
   Defined by a point, from vectors.h, and a radius */
struct Circle : public RigidBody {
    Circle(): RigidBody(), radius(1) {}
    Circle(double r, double m, Point *p, Vector *v, Vector *a): RigidBody(m, p, v, a), radius(r) {}
    double radius;  // radius of circle

    bool collides_with(Circle& B) {     // circle collides with circle
        double r = radius + B.radius;
        r *= r;
        double y = pow(pos->x - B.pos->x, 2);
        double z = pow(pos->y - B.pos->y, 2);
        return r > (y + z);
    }

    bool collides_with(Rectangle& B) {  // circle collides with rectangle
        Rectangle aabb(2 * radius, 2 * radius, RigidBody::mass, RigidBody::pos, RigidBody::vel, RigidBody::accel);

        if (!aabb.collides_with(B)) return false;    // false if aabb of circle doesn't collide with rectangle

        if (RigidBody::pos->x < B.max->x and RigidBody::pos->x > B.min->x)
            return true;
        if (RigidBody::pos->y < B.max->y and RigidBody::pos->y > B.min->y)
            return true;

        // corners = {bot_left, top_right, top_left, bot_right}
        vector<Point*> corners = {B.min, B.max, new Point(B.min->x, B.max->y), new Point(B.max->x, B.min->y)};

        for (auto corner : corners) {   // checking if corner penetrates circle
            double y = pow(RigidBody::pos->x - corner->x, 2);
            double z = pow(RigidBody::pos->y - corner->y, 2);
            if (radius > (y + z))
                return true;
        }
    }
};

void apply_force(RigidBody& rb, Vector f) {
    rb.forces.push_back(f);
    rb.set_accel(rb.get_netf());
}

void move(RigidBody& rb, float dt) {
    rb.vel->x_cmp += rb.accel->x_cmp * dt;
    rb.vel->y_cmp += rb.accel->y_cmp * dt;
    rb.vel->mag = get_mag(rb.vel->x_cmp, rb.vel->y_cmp);
    rb.pos->x += rb.vel->x_cmp * dt;
    rb.pos->y += rb.vel->y_cmp * dt;
}

ostream& operator<<(ostream& os, RigidBody& rbd) {
        string op = "pos[x: " + to_string(rbd.pos->x) + ", y: " + to_string(rbd.pos->y) + "]\nvel[x: " + \
        to_string(rbd.vel->x_cmp) + ", y: " + to_string(rbd.vel->y_cmp) + ", abs: " + to_string(rbd.vel->mag) + "]";
        os << op << endl;
        return os;
}

