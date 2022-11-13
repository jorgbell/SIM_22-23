#pragma once
#include "WindForceGenerator.h"
class WhirlwindForceGenerator :
    public WindForceGenerator
{
public:
    WhirlwindForceGenerator(const Vector3& windVel, const Vector3& windPos, double windRadius, const Vector4& color, float k1, float k2 = 0);
    virtual void updateForce(Particle* particle, double t);

};

