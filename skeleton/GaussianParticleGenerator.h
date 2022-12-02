#pragma once
#include "ParticleGenerator.h"
#include <vector>
class GaussianParticleGenerator :
    public ParticleGenerator
{
public:
    GaussianParticleGenerator(string Name, Vector3 pos, Vector3 vel, int n, Particle* b, Vector3 deviationPos, Vector3 deviationVel, double life = -1, double prob = 0.5):
        ParticleGenerator(Name, pos, vel, Vector4(0.5, 0, 1, 1), n, b, life, prob), std_dev_pos(deviationPos), std_dev_vel(deviationVel){}
    virtual list<Particle*> generateParticles();
private:
    Vector3 std_dev_pos, std_dev_vel;
    double std_dev_t;

};

