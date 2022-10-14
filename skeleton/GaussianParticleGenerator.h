#pragma once
#include "ParticleGenerator.h"
class GaussianParticleGenerator :
    public ParticleGenerator
{
public:
    GaussianParticleGenerator(Vector3 pos, Vector3 vel, int n, Particle* b, double prob, string t = " "/*to_string(generatorID++)*/);
    virtual list<Particle*> generateParticles();
private:
    Vector3 std_dev_pos, std_dev_vel;
    double std_dev_t;

};

