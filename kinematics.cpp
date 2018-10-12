#pragma once

#include "rigidbody.h"

void RigidBody::set_vel(Vector *v) {vel = v;}

void RigidBody::set_accel() {
    auto net_force = get_netf();
    auto acc_head = new Point(net_force.x_cmp / mass, net_force.y_cmp / mass);
    accel = new Vector(net_force.tail, acc_head);
}

Vector RigidBody::get_netf() {
    if (forces.empty()) return {new Point, new Point};

    auto netf = forces[0];
    for (int i = 1; i < forces.size(); i++)
        netf = netf + forces[i];
    return netf;
}

void Rectangle::set_corners() {
    min = new Point(RigidBody::pos->x - length / 2, RigidBody::pos->y - width / 2);
    max = new Point(RigidBody::pos->x + length / 2, RigidBody::pos->y + width / 2);
}

bool Rectangle::collides_with(Rectangle *r) {
    set_corners();
    r->set_corners();
    if (max->x < r->min->x or min->x > r->max->x)
        return false;
    return !(max->y < r->min->y or min->y > r->max->y);
}

bool Rectangle::collides_with(Circle *c) {
    auto aabb = new Rectangle(2 * c->radius, 2 * c->radius, c->mass, c->pos, c->vel, c->accel);

    if (!collides_with(aabb)) return false;

    if (c->pos->x < max->x and c->pos->x > min->x)
        return true;
    if (c->pos->y < max->y and c->pos->y > min->y)
        return true;

    vector<Point*> corners = {min, max, new Point(min->x, max->y), new Point(max->x, min->y)};

    for (auto corner : corners) {
        double y = pow(pos->x - corner->x, 2);
        double z = pow(pos->y - corner->y, 2);
        if (c->radius > (y + z))
            return true;
    }
}

bool Circle::collides_with(Rectangle *r) {
    auto aabb = new Rectangle(2 * radius, 2 * radius, RigidBody::mass, RigidBody::pos, RigidBody::vel, RigidBody::accel);

    if (!aabb->collides_with(r)) return false;

    if (RigidBody::pos->x < r->max->x and RigidBody::pos->x > r->min->x)
        return true;
    if (RigidBody::pos->y < r->max->y and RigidBody::pos->y > r->min->y)
        return true;

    vector<Point*> corners = {r->min, r->max, new Point(r->min->x, r->max->y), new Point(r->max->x, r->min->y)};

    for (auto corner : corners) {
        double y = pow(RigidBody::pos->x - corner->x, 2);
        double z = pow(RigidBody::pos->y - corner->y, 2);
        if (radius > (y + z))
            return true;
    }
}

bool Circle::collides_with(Circle *c) {
    double r = radius + c->radius;
    r *= r;
    double y = pow(pos->x - c->pos->x, 2);
    double z = pow(pos->y - c->pos->y, 2);
    return r > (y + z);
}

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

