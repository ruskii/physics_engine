#include <iostream>
#include <vector>
#include "rigidbody.h"
using namespace std;

template <typename object>
void run_sim(float sim_time, float dt, vector<object> rbds) {
    float current_time = 0;
    while (current_time < sim_time) {
        for (auto &rbd : rbds) {
            cout << rbd << endl;
            for (auto &other : rbds) {      // checking if object collides with other objects
                if (&other == &rbd) continue;   // find more efficient way than for loop

                if (rbd.collides_with(other))
                    cout << "COLLISION DETECTED\n" << endl;
            }
            move(rbd, dt);
        }
        cout << "----------------------------------" << endl;
        current_time += dt;
        usleep(dt * 1000);
    }
}

int main() {
    Circle a;
    Vector force(new Point, new Point(1, 0));
    apply_force(a, force);

    Rectangle b(2, 2, 1, new Point(3, 0), new Vector, new Vector);

    vector<RigidBody> rbds = {a, b};
    run_sim(20, 1, rbds);

    return 0;
}
