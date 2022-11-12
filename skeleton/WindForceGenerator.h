#pragma once
#include "ForceGenerator.h"
class WindForceGenerator :
    public ForceGenerator
{
public:
    WindForceGenerator(const Vector3& w, float k1, float k2 = 0);
    virtual void updateForce(Particle* particle, double t);
    inline void setWindVel(Vector3 w) { _windVelocity = w; }

protected:
    float _k1; //coeficiente de rozamiento 1
    float _k2; //coeficiente de rozamiento 1
    Vector3 _windVelocity;

};

