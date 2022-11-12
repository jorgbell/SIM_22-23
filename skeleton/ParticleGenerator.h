#pragma once
#include "Particle.h"
#include "ForceGenerator.h"
#include <string>
#include <list>
using namespace std;

class ParticleGenerator {
public:
	ParticleGenerator(string Name, Vector3 pos, Vector3 vel, int n, Particle* b, double lifetime = -1, double prob = 1.0) :
		_origin(pos), _velMedia(vel), _nParticles(n), _name(Name), _probability(prob), _lifetime_media(lifetime)
	{
		setBaseParticle(b);
	}

	void setBaseParticle(Particle* model) {
		if(_baseParticle != nullptr) 
			delete _baseParticle; 
		_baseParticle = model;
		_baseParticle->DeregisterParticle();
	}
	Particle* getBaseParticle() { return _baseParticle;}

	virtual list<Particle*> generateParticles() = 0;
	string getParticleGeneratorName() { return _name; }

	void addForceGenerator(ForceGenerator* fg) {
		_forceGeneratorsPool.push_back(fg);
	}
	void eraseForceGenerator(string name) {
		bool encontrado = false;
		list<ForceGenerator*>::iterator it = _forceGeneratorsPool.begin();
		ForceGenerator* fg;

		while (!encontrado && it != _forceGeneratorsPool.end()) {
			fg = (*it);
			if (fg->_name == name)
				encontrado = true;
			else
				it++;
		}

		if (encontrado)
			_forceGeneratorsPool.erase(it);
	}

	list<ForceGenerator*> getForceGenerators() { return _forceGeneratorsPool; }
protected:
	string _name;
	Vector3 _origin;
	Vector3 _velMedia;
	double _probability;
	double _lifetime_media;
	int _nParticles;
	Particle* _baseParticle = nullptr;
	list<ForceGenerator*> _forceGeneratorsPool;


};