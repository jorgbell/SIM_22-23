#pragma once
#include "ForceGenerator.h"
class WindForceGenerator :
    public ForceGenerator
{
public:
    WindForceGenerator(bool render, const Vector3& windVel, const Vector3& windPos, double windRadius, const Vector4& color, float k1, float k2 = 0);
    ~WindForceGenerator();
    virtual void updateForce(Particle* particle, double t);
    inline void setWindVel(Vector3 w) { _windVelocity = w; }

protected:
    float _k1; //coeficiente de rozamiento 1
    float _k2; //coeficiente de rozamiento 1
    Vector3 _windVelocity;
    Transform regionTransform;
    RenderItem* region = nullptr;;
    double regionRadius;
    bool collides(const Vector3& pos);

};

