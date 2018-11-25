#include <cmath>
#include <iostream>
#include "rigidbody.h"

using namespace std;

void RigidBody::set_pos(Point *p) {pos = p;}

void RigidBody::set_vel(Vector *v) {
    vel = v;
    vel->mag = magnitude(vel->x_cmp, vel->y_cmp);
}

void RigidBody::set_accel(Vector *a) {accel = a;}

void RigidBody::update_accel() {
    sum_forces();
    auto accel_head = new Point(net_force.x_cmp / mass, net_force.y_cmp / mass);
    set_accel(new Vector(net_force.tail, accel_head));
}

void RigidBody::sum_forces() {      // try with lambdas
    if (!forces.empty()) {
        net_force = forces[0];

        for (int i = 1; i < forces.size(); i++)
            net_force += forces[i];     // need to test this
    }
}

Vector RigidBody::get_netforce() const {return net_force;}

void Rectangle::set_corners() {
    min = new Point(RigidBody::pos->x - length / 2, RigidBody::pos->y - width / 2);
    max = new Point(RigidBody::pos->x + length / 2, RigidBody::pos->y + width / 2);
}

void Rectangle::set_pos(Point *p) {
    pos = p;
    set_corners();
}

bool Rectangle::collides_with(const Rectangle &r) const {
    if (max->x < r.min->x or min->x > r.max->x)
        return false;
    return !(max->y < r.min->y or min->y > r.max->y);
}

bool Rectangle::collides_with(const Circle &c) const {
    Rectangle aabb(2 * c.radius, 2 * c.radius, c.mass, c.pos, c.vel, c.accel);

    if (collides_with(aabb)) {

        if (c.pos->x < max->x and c.pos->x > min->x)
            return true;
        if (c.pos->y < max->y and c.pos->y > min->y)
            return true;

        vector<Point*> corners = {min, max, new Point(min->x, max->y), new Point(max->x, min->y)};

        for (auto corner : corners) {
            double xpos_to_corner = pow(pos->x - corner->x, 2);
            double ypos_to_corner = pow(pos->y - corner->y, 2);
            if (c.radius > (xpos_to_corner + ypos_to_corner))
                return true;
        }
        return false;
    } else return false;
}

bool Circle::collides_with(const Rectangle &r) const {  // must get rid of code duplication from above
/*
    Rectangle aabb(2 * radius, 2 * radius, RigidBody::mass, RigidBody::pos, RigidBody::vel, RigidBody::accel);

    if (aabb.collides_with(r)) {

        if (RigidBody::pos->x < r.max->x and RigidBody::pos->x > r.min->x)
            return true;
        if (RigidBody::pos->y < r.max->y and RigidBody::pos->y > r.min->y)
            return true;

        vector<Point*> corners = {r.min, r.max, new Point(r.min->x, r.max->y), new Point(r.max->x, r.min->y)};

        for (auto corner : corners) {
            double xpos_to_corner = pow(RigidBody::pos->x - corner->x, 2);
            double ypos_to_corner = pow(RigidBody::pos->y - corner->y, 2);
            if (radius > (xpos_to_corner + ypos_to_corner))
                return true;
        }
        return false;
    } else return false;
*/
    return r.collides_with(*this);
}

bool Circle::collides_with(const Circle &c) const {
    double r = radius + c.radius;
    r *= r;
    double x_dist = pow(pos->x - c.pos->x, 2);
    double y_dist = pow(pos->y - c.pos->y, 2);
    return r > (x_dist + y_dist);
}

void apply_force(RigidBody& rb, const Vector &force) {
    rb.forces.push_back(force);
    rb.update_accel();
}

void move(RigidBody& rb, float dt) {
    auto new_vel_x = rb.vel->x_cmp + rb.accel->x_cmp * dt;
    auto new_vel_y = rb.vel->y_cmp + rb.accel->y_cmp * dt;
    rb.set_vel(new Vector(rb.pos, new Point(new_vel_x, new_vel_y)));

    auto new_pos_x = rb.pos->x + rb.vel->x_cmp * dt;
    auto new_pos_y = rb.pos->y + rb.vel->y_cmp * dt;
    rb.set_pos(new Point(new_pos_x, new_pos_y));
}

bool scan_collision(const RigidBody &a, RigidBody &b) {     // find better way to call collide function
    const auto rectangle = dynamic_cast<Rectangle*>(&b);

    if (rectangle)
        return a.collides_with(*rectangle);
    else {
        const auto circle = dynamic_cast<Circle*>(&b);
        return a.collides_with(*circle);
    }
}

