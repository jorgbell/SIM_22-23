#pragma once
#include "ParticleGenerator.h"
#include "Firework.h"
class FireworksGenerator : public ParticleGenerator
{
public:
	FireworksGenerator(int nParticles = 40);

	//este generateParticles vendría a ser el explode(), generia particulas normales
	virtual list<Particle*> generateParticles();
	list<Firework*> generateFireworks(vector<payload> p);
private:

};

