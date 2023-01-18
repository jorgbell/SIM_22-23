#pragma once
#include "ForceGenerator.h"
class JetpackForceGenerator :
    public ForceGenerator
{
public:
    JetpackForceGenerator(float force, float fuel, float cost, bool* inputUp, std::string* text);
    ~JetpackForceGenerator();
    virtual void updateForce(Particle* particle, double t);

protected:
    void recarga();
    std::string* display;
    float _force;
    bool* isGoingUp;
    float _maxFuel; float _fuel;
    float _cost;
};

