#pragma once
#include "ParticleSystem.h"
#include "FireworksGenerator.h"
class FireworksSystem : public ParticleSystem
{
public:
	//la posici�n ser� para asignarla a la primera part�cula
	FireworksSystem(Firework* first, int maxExplosions = INT_MAX);
	~FireworksSystem();
	virtual void update(double t);
private:
	virtual void checkParticles() override;

	//numero m�ximo de iteraciones de creacion de fireworks.
	//se limita para que no haya una generaci�n infinita exponencial de fireworks.
	int maxFireworksGeneration;
	int nExplosions;
	FireworksGenerator* _fireworksGen;
};

