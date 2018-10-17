#include <iostream>
#include <vector>
#include "vectors.h"
#include "rigidbody.h"

using namespace std;

/* While simulation run time hasn't been reached, iterate through all RigidBodies
   and check for a collision with all other RigidBodies, and update positions as necessary
*/
void run_sim(vector<RigidBody*> rbds, int sim_time, int tick) {
    float current_time = 0;
    while (current_time < sim_time) {
        for (auto &rbd : rbds) {
            cout << *rbd << endl;
            for (auto &other : rbds) {
                if (&other == &rbd) continue;

                if (scan_collision(rbd, other))
                    cout << "COLLISION DETECTED\n" << endl;
            }
            move(*rbd, tick);
        }
        cout << "----------------------------------" << endl;
        current_time += tick;
        usleep(tick * 1000);
    }
}

int main() {
    auto a = new Circle;
    a->set_vel(new Vector(new Point, new Point(1, 0)));

    auto b = new Circle(1, 1, new Point(5, 0), new Vector, new Vector);
    auto c = new Rectangle(2, 2, 1, new Point(10, 0), new Vector, new Vector);

    std::vector<RigidBody*> objects = {a, b, c};

    run_sim(objects, 20, 1);

    return 0;
}
