#include "rigidbody.h"

using namespace std;

void RigidBody::set_vel(Vector *v) {vel = v;}

void RigidBody::set_accel() {
    sum_forces();
    auto netf = get_netforce();
    auto accel_head = new Point(netf.x_cmp / mass, netf.y_cmp / mass);
    accel = new Vector(net_force.tail, accel_head);
}

void RigidBody::sum_forces() {
    if (!forces.empty()) {
        net_force = forces[0];

        for (int i = 1; i < forces.size(); i++)
            net_force = net_force + forces[i];
    }
}

Vector RigidBody::get_netforce() const {return net_force;}

void Rectangle::set_corners() {
    min = new Point(RigidBody::pos->x - length / 2, RigidBody::pos->y - width / 2);
    max = new Point(RigidBody::pos->x + length / 2, RigidBody::pos->y + width / 2);
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

bool Circle::collides_with(const Rectangle &r) const {
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
    rb.set_accel();
}

void move(RigidBody& rb, float dt) {
    rb.vel->x_cmp += rb.accel->x_cmp * dt;
    rb.vel->y_cmp += rb.accel->y_cmp * dt;
    rb.vel->mag = magnitude(rb.vel->x_cmp, rb.vel->y_cmp);
    rb.pos->x += rb.vel->x_cmp * dt;
    rb.pos->y += rb.vel->y_cmp * dt;

    if (auto rect = dynamic_cast<Rectangle*>(&rb))
        rect->set_corners();
}

bool scan_collision(const RigidBody &a, RigidBody &b) {
    const auto b_rect = dynamic_cast<Rectangle*>(&b);

    if (b_rect)
        return a.collides_with(*b_rect);
    else {
        const auto b_circ = dynamic_cast<Circle*>(&b);
        return a.collides_with(*b_circ);
    }
}

ostream& operator<<(ostream& os, const RigidBody& rbd) {
    string op = "pos[x: " + to_string(rbd.pos->x) + ", y: " + to_string(rbd.pos->y) + "]\nvel[x: " + \
    to_string(rbd.vel->x_cmp) + ", y: " + to_string(rbd.vel->y_cmp) + ", abs: " + to_string(rbd.vel->mag) + "]";
    os << op << endl;
    return os;
}

