#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class BuoyancyFG : public ForceGenerator {
public:
	BuoyancyFG(float h, float V, float d, Vector3 liquid_pos);

	virtual void updateForce(Particle* particle, double t);

	virtual ~BuoyancyFG();

	void setVolume(float v) { _volume = v; }

	float getVolume() { return _volume; }

protected:
	float _height, _volume, _liquid_density;

	Particle* _liquid_particle; //For representation;

};