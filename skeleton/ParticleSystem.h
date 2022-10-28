#pragma once
#include <list>
#include <string>
#include "Particle.h"
#include "ParticleGenerator.h"
using namespace std;

//ParticleSystem es el sistema que guarda los distintos generadores que haya y todas las particulas que haya en el sistema.

class ParticleSystem {
public:
	ParticleSystem(){};
	~ParticleSystem();
	virtual void update(double t);
	ParticleGenerator* getParticleGenerator(string name);
	virtual void add(ParticleGenerator* p) { _generatorsPool.push_back(p); }
	virtual void erase(string name);
	int getNumGenerators() { return _generatorsPool.size(); }
protected:
	list<Particle*> _particlePool;
	list<ParticleGenerator*> _generatorsPool;
	virtual void checkParticles();

private:

};