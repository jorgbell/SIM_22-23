#pragma once
#include "ParticleGenerator.h"
#include "Firework.h"
class FireworksGenerator : public ParticleGenerator
{
public:
	FireworksGenerator();

	//este generateParticles vendría a ser el explode(), generia particulas normales
	virtual list<Particle*> generateParticles();
	list<Firework*> generateFireworks(FireworksType t);
private:

};

