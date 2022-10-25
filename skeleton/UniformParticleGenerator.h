#pragma once
#include "ParticleGenerator.h"
class UniformParticleGenerator :
    public ParticleGenerator
{
public:
    UniformParticleGenerator(string Name, Vector3 pos, Vector3 vel, int n, Particle* b, Vector3 deviationPos, Vector3 deviationVel, double life = -1, double prob = 0.5) :
        ParticleGenerator(Name, pos, vel, n, b, life, prob){}
    virtual list<Particle*> generateParticles();
private:

};

