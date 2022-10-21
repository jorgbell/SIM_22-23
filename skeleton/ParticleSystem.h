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
	void update(double t);
	ParticleGenerator* getParticleGenerator(string name);
	void add(ParticleGenerator* p) { _generatorsPool.push_back(p); }
	void erase(string name);
	int getNumGenerators() { return _generatorsPool.size(); }
protected:

private:
	list<Particle*> _particlePool;
	list<ParticleGenerator*> _generatorsPool;
	//void generateFireworkSystem();
	void checkParticles();

};