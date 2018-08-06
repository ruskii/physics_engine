#include <iostream>
#include <utility>
#include <unistd.h>
#include <cmath>
#include <vector>
#include "vectors.h"
#include "point.h"
#include <typeinfo>

// To detect collisions by defining rigid bodies for 2D shapes by using "Is-A" relationship

struct RigidBody{
    RigidBody() : mass(1), pos(new Point), vel(new Vector), accel(new Vector) {}
    RigidBody(double m, Point *p, Vector *v, Vector *a) : mass(m), pos(p), vel(v), accel(a) {}
    double mass;
    double restitution = 0.5;//bounciness
    Point *pos;
    Vector *vel;
    Vector *accel;
    vector<Vector> forces;          // stores all forces acting on particle
    friend ostream& operator<<(ostream& os, RigidBody& rbd);

    void set_vel(Vector *v) {vel = v;}

    void set_accel() {  // returns acceleration from applying force to particle //parameter Vector f removed**
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
        cout << "rigid/n";
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
        /*if (max->x < B.min->x or min->x > B.max->x)
            return false;
        return !(max->y < B.min->y or min->y > B.max->y);*/
        cout << "rec/n";
        if(max->x < B.min->x or min->x > B.max->x) return true;
        if(max->y < B.min->y or min->y > B.max->y) return true;

        return false;
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
        cout << "circ/n";
        double r = radius + B.radius;
        r *= r;
        double y = pow(pos->x - B.pos->x, 2);
        double z = pow(pos->y - B.pos->y, 2);
        return r > (y + z);
    }

    bool collides_with(Rectangle& B) {  // circle collides with rectangle
        cout << "circ/n";
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
    rb.set_accel(); //accepts no args
}


void move(RigidBody& rb, double dt) {
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

//functions for collision resolution

Vector get_normal(RigidBody& rbdA, RigidBody& rbdB) {
    if(typeid(rbdA).name() == "Circle" && typeid(rbdB).name() == "Circle") {
        //different between A and B
        Vector dif(rbdB.pos, rbdA.pos);

        //avoid divide by 0
        if (dif.mag != 0) {
            //converting the difference into a unit vector as normal
            return (1 / dif.mag) * dif;
        } else {  //if length is indeed 0, replace with this
            Point *a = new Point(1, 0);
            Point *b = new Point(0, 0);
            return Vector(a, b);
        }
    }
}

// BROKE THESE INTO 4 OVERLOAD FUNCTIONS

Vector get_normal(Rectangle &rbdA, Rectangle &rbdB) {
    // Create a vector that points from rdbA to rdbB
    Vector ab(rbdA.pos, rbdB.pos);

    // this next few lines are to find the axis that has the least penetration
    // first, calculate x axis
    double aXExtent = (rbdA.max->x - rbdA.min->x) / 2;
    double bXExtent = (rbdB.max->x - rbdB.min->x) / 2;

    double aYExtent = (rbdA.max->y - rbdA.min->y) / 2;
    double bYExtent = (rbdB.max->y - rbdB.min->y) / 2;

    double xAxis = aXExtent + bXExtent - abs(ab.x_cmp);
    double yAxis = aYExtent + bYExtent - abs(ab.y_cmp);

    Point *a;
    Point *b;
// i have 200 iq today vincent agrees
    if (xAxis >= 0) {
        if (yAxis > 0) {
            if (xAxis > yAxis) {
                if (ab.x_cmp < 0) {
                    return Vector(a = new Point(0,0), b = new Point(0, -1)); //+5IQ
                    // :^)
                }
                else {
                    a = new Point(0, 0); //-1 IQ
                    b = new Point(0, 1); // -1 IQ
                    return Vector(a, b);
                    // :^)
                }
            }
            else {
                if (ab.y_cmp < 0) {
                    a = new Point(0, 0); // -1 IQ
                    b = new Point(-1, 0); // -1 IQ
                    return Vector(a, b);
                    // :^)
                }
                else {
                    a = new Point(0, 0); // -1 IQ
                    b = new Point(1, 0); // -1 IQ
                    return Vector(a, b);
                    // :^)
                }
            }
        }
    }
}

double clamp(double num, double min, double max){
    if(num < min){
        return min;
    }
    else if(num > max){
        return max;
    }
    else
        return num;
}


Vector get_normal(Rectangle &rbdA, Circle &rbdB) {
/* TO BE CONTINUED. . ..
 *
 *
    // Create a vector that points from rdbA to rdbB
    Vector ab(rbdA.pos, rbdB.pos);
    Vector closest = ab;

    // for rectangle
    double xExtent = (rbdA.max->x, rbdA.min->x) / 2;
    double yExtent = (rbdA.max->y, rbdA.min->y) / 2;

    closest.x_cmp = clamp(-xExtent, xExtent, closest.x_cmp);
    closest.y_cmp = clamp(-yExtent, yExtent, closest.y_cmp);
    // To understand clamp https://www.geeksforgeeks.org/stdclamp-in-cpp-17/
*/
}

Vector get_normal(Circle &rbdA, Rectangle &rbdB) {
    return get_normal(rbdB, rbdA); //+10 IQ
}




/////////////////////////////////
// NEED TO RESOLVE MORE ERRORS //
/////////////////////////////////

/*
void resolveCollision(RigidBody &rbdA, RigidBody &rbdB, Vector normal) {
    //relative velocity
    Vector relativeVel = rbdB.vel-rbdA.vel;

    // calculate dot product for relative velocity vector and normal vector
    // and get magnitude of vector
    double mag = relativeVel * normal;

    double bounce;//min restitution between rbdA and rbdB
    bounce = min(rbdA.restitution, rbdB.restitution);

    double j = -(1 + bounce) * mag;
    j /= 1/rbdA.mass + 1/rbdB.mass;

    Vector impulse = j * normal;
    rbdA.vel = rbdA.vel - (1/rbdA.mass * impulse);
    rbdB.vel += 1/rbdB.mass * impulse;
}*/