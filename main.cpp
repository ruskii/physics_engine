#include <iostream>
#include <vector>
#include "world.h"

using namespace std;

/* While simulation run time hasn't been reached, iterate through all RigidBodies
   and check for a collision with all other RigidBodies, and update positions as necessary
*/
void run_sim(Simulation s) {
    float current_time = 0;
    while (current_time < s.sim_time) {
        for (auto &rbd : s.rbds) {
            cout << *rbd << endl;
            for (auto &other : s.rbds) {      // checking if object collides with other objects
                if (&other == &rbd) continue;   // find more efficient way than for loop

                if (scan_collision(rbd, other))
                    cout << "COLLISION DETECTED\n" << endl;
            }
            move(*rbd, s.dt);
        }
        cout << "----------------------------------" << endl;
        current_time += s.dt;
        usleep(s.dt * 1000);
    }
}

int main() {
    auto a = new Circle;
    a->set_vel(new Vector(new Point, new Point(1, 0)));

    auto b = new Circle(1, 1, new Point(5, 0), new Vector, new Vector);
    auto c = new Rectangle(2, 2, 1, new Point(10, 0), new Vector, new Vector);

    vector<RigidBody*> rbds = {a, b, c};
    Simulation sim(rbds, 20, 1);

    run_sim(sim);

    return 0;
}
