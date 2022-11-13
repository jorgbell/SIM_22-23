#pragma once
#include "ParticleGenerator.h"
class UniformParticleGenerator :
    public ParticleGenerator
{
public:
    UniformParticleGenerator(string Name, Vector3 pos, Vector3 vel, Vector4 color, int n, Particle* b, Vector3 poswidth, Vector3 velwidth, double life = -1, double prob = 0.5) :
        ParticleGenerator(Name, pos, vel, color, n, b, life, prob), _velwidth(velwidth), _poswidth(poswidth) {}
    virtual list<Particle*> generateParticles();
private:
    Vector3 _velwidth, _poswidth;
};

