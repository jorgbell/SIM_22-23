#pragma once
#include "ParticleGenerator.h"
#include "Firework.h"
class FireworksGenerator : public ParticleGenerator
{
public:
	FireworksGenerator(Firework* first, int nParticles = 40);

	//este generateParticles vendr�a a ser el explode(), generia particulas normales
	virtual list<Particle*> generateParticles();
	void setLastExploded(Firework* lastExploded) { _lastExploded = lastExploded; }
private:
	Firework* _lastExploded;
};

