#pragma once
#include "SpringForceGenerator.h"
class BungeeFG :
    public SpringForceGenerator
{
public:
    BungeeFG(float k, float resting_length,Particle* other ):
        SpringForceGenerator(k, resting_length, other)
    {}

    virtual void updateForce(Particle* particle, double t);

    ~BungeeFG(){};
};

