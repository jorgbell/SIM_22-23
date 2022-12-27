#pragma once
#include <list>
#include <string>
#include "Particle.h"
#include "ParticleGenerator.h"
#include "ParticleForceRegistry.h"
using namespace std;

//ParticleSystem es el sistema que guarda los distintos generadores que haya y todas las particulas que haya en el sistema.

class ParticleSystem {
public:
	ParticleSystem(){};
	~ParticleSystem();
	virtual void clean();
	virtual void clear();
	virtual void update(double t);
	ParticleGenerator* getParticleGenerator(string name);
	virtual void addParticleGenerator(ParticleGenerator* p) { _generatorsPool.push_back(p); }
	virtual void addToForceRegistry(ForceGenerator* fg, Particle* p) { _particleForceRegistry.addRegistry(fg, p); 
	if (!isInPool(p)) 
		addToParticlePool(p);
	}
	virtual void addToParticlePool(Particle* p) { _particlePool.push_back(p); }
	virtual bool isInPool(Particle* p) { return (std::find(_particlePool.begin(), _particlePool.end(), p)!=_particlePool.end()); }
	virtual void erase(string name);
	int getNumGenerators() { return _generatorsPool.size(); }
protected:
	list<Particle*> _particlePool;
	list<ParticleGenerator*> _generatorsPool;
	virtual void checkParticles();
	ParticleForceRegistry _particleForceRegistry;

private:

};