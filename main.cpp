#include <iostream>
#include <vector>
#include "rigidbody.h"
using namespace std;

// Testing a change
// Testing v2
//vincent 

template <typename object>
void run_sim(float sim_time, float dt, vector<object> rbds) {
    float current_time = 0;

    while (current_time < sim_time) {
        for (auto &rbd : rbds) {
            cout << typeid(rbd).name() << endl;
            cout << rbd << endl;
            for (auto &other : rbds) {      // checking if object collides with other objects
                if (&other == &rbd) continue;   // find more efficient way than for loop

                if (rbd.collides_with(other)) {
                    cout << "COLLISION DETECTED\n" << endl;
                    // First, we get the normal then we call resolve collision

                    // vector norm = get_normal(rbd, other);// solve with overloaded function
                    // resolveCollision(&rbd, &other, norm);//resolve if colliding
                }
                move(rbd, dt);
            }
            cout << "----------------------------------" << endl;
            current_time += dt;
            usleep(dt * 1000);
        }
    }
}

int main() {
    Vector v1(new Point(0,0), new Point(1, 0));
//    Vector v2(new Point, new Point(3, 0));

//    cout << v1 << "\n" << v2 << endl;
//    v1 -= v2;

 //   cout << v1 << endl;

/*    Circle a;
    Vector force(new Point, new Point(1, 0));
    apply_force(a, force);
    */
    //        (l,w, m , new Point (center) , new vel, new accel );
    Rectangle a(6, 4, 1, new Point(-6, 2), new Vector(v1), new Vector);
    Rectangle b(6, 4, 1, new Point(3, 2), new Vector, new Vector);

    vector<Rectangle> rbds = {a, b};
    cout << typeid(rbds[0]).name() << endl;
    cout << typeid(b).name() << endl;
    run_sim(20, 1, rbds);

    return 0;
}
