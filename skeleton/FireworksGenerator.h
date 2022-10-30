#pragma once
#include "ParticleGenerator.h"
#include "Firework.h"
class FireworksGenerator : public ParticleGenerator
{
public:
	FireworksGenerator();
	~FireworksGenerator() { delete _baseParticle; }
	//este generateParticles vendría a ser el explode(), generia particulas normales
	virtual list<Particle*> generateParticles();
	void setLastExploded(Firework* lastExploded) { _lastExploded = lastExploded; }
private:
	Firework* _lastExploded;
};

