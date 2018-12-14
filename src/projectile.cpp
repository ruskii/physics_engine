#include "projectile.h"

using namespace std;

void Projectile::update_accel() {
    sum_forces();
    auto accel_head = new Point(net_force.x_cmp / mass, net_force.y_cmp / mass);
    accel = new Vector(net_force.tail, accel_head);
}

void Projectile::sum_forces() {
    if (!forces.empty()) {
        net_force = forces[0];

        for (int i = 1; i < forces.size(); i++)
            net_force += forces[i];
    }
}
