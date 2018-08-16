#pragma once
#include "shapes.h"
#include <utility>
#include <vector>

struct Simulation {
    Simulation(vector<RigidBody*> rbds, float st, float dt) : rbds(std::move(rbds)), sim_time(st), dt(dt) {}
    vector<RigidBody*> rbds;
    float sim_time;
    float dt;
};
