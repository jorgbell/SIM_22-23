#pragma once
#include "ParticleSystem.h"
#include "FireworksGenerator.h"
class FireworksSystem : public ParticleSystem
{
public:
	//la posición será para asignarla a la primera partícula
	FireworksSystem(int maxExplosions = INT_MAX);
	~FireworksSystem();
	virtual void update(double t);
	void startFire(Vector3 initPos, Vector3 initVel, FireworksType type = FIREWORK_5);
private:
	virtual void checkParticles() override;

	//numero máximo de iteraciones de creacion de fireworks.
	//se limita para que no haya una generación infinita exponencial de fireworks.
	int maxFireworksGeneration;
	int nExplosions;
	FireworksGenerator* _fireworksGen;
};

