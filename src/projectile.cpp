#include "projectile.h"

using namespace std;

void RigidBody::update_accel() {
    sum_forces();
    auto accel_head = new Point(net_force.x_cmp / mass, net_force.y_cmp / mass);    // a = F / m
    accel = new Vector(net_force.tail, accel_head);
}

void RigidBody::sum_forces() {
    if (!forces.empty()) {
        net_force = forces[0];

        for (int i = 1; i < forces.size(); i++)
            net_force += forces[i];
    }
}

void apply_force(RigidBody& rb, const Vector &force) {
    rb.forces.push_back(force);
    rb.update_accel();
}

void move(RigidBody& rb, float dt) {
	// linear movement
    rb.vel->x_cmp += rb.accel->x_cmp * dt;
    rb.vel->y_cmp += rb.accel->y_cmp * dt;
    rb.vel->mag = magnitude(rb.vel->x_cmp, rb.vel->y_cmp);
    rb.shape.shift(*rb.vel, dt);

    // angular movement
    rb.angular_vel += rb.torque * dt;	// TODO: calculate torque function
    // calculate target angle for frame
    // rb.shape.rotate(target_angle, dt);
}
