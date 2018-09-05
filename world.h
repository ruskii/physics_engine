#pragma once
#include "shapes.h"
#include <utility>
#include <vector>

// Currently, a basic simulation contains a set of RigidBodies, a simulation run time, and a time increment
struct Simulation {
    Simulation(vector<RigidBody*> rbds, float st, float dt) : rbds(std::move(rbds)), sim_time(st), dt(dt) {}
    vector<RigidBody*> rbds;
    float sim_time;
    float dt;
};
