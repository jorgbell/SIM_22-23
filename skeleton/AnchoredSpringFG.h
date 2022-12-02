#pragma once
#include "SpringForceGenerator.h"
class AnchoredSpringFG :
    public SpringForceGenerator
{
public:
    AnchoredSpringFG(double k, double resting, const Vector3& anchor_pos);

    virtual void updateForce(Particle* particle, double t) { SpringForceGenerator::updateForce(particle,t); }

    ~AnchoredSpringFG();
};

