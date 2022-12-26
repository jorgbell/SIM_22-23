#pragma once
#include "WindRBFG.h"
class WhirlwindRBFG :
    public WindRBFG
{
public:
    WhirlwindRBFG(const Vector3& windPos, double windRadius, const Vector4& color, float k1, float k2 = 0);
    virtual void updateForce(DynamicRigidBody* particle, double t);

};

