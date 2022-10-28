#pragma once
#include "ParticleSystem.h"
#include "FireworksGenerator.h"
class FireworksSystem : public ParticleSystem
{
public:
	FireworksSystem(int maxExplosions = INT_MAX);
	~FireworksSystem();
	virtual void update(double t);


private:
	virtual void checkFireworks();

	//numero máximo de iteraciones de creacion de fireworks.
	//se limita para que no haya una generación infinita exponencial de fireworks.
	int maxFireworksGeneration;
	int nExplosions;
	FireworksGenerator* _fireworksGen;
	list<Firework*> _fireworksPool;
};

