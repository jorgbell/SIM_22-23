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

	//numero m�ximo de iteraciones de creacion de fireworks.
	//se limita para que no haya una generaci�n infinita exponencial de fireworks.
	int maxFireworksGeneration;
	int nExplosions;
	FireworksGenerator* _fireworksGen;
	list<Firework*> _fireworksPool;
};

