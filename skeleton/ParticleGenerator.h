#pragma once
#include "Particle.h"
#include <string>
#include <list>
using namespace std;

class ParticleGenerator {
public:
	ParticleGenerator(string Name, Vector3 pos, Vector3 vel, int n, Particle* b, double lifetime = -1, double prob = 1.0) :
		_origin(pos), _velMedia(vel), _nParticles(n), _baseParticle(b), _name(Name), _probability(prob), _lifetime_media(lifetime)
	{}

	void setBaseParticle(Particle* model) { _baseParticle = model; }

	virtual list<Particle*> generateParticles() = 0;
	string getGeneratorName() { return _name; }

protected:
	string _name;
	Vector3 _origin;
	Vector3 _velMedia;
	double _probability;
	double _lifetime_media;
	int _nParticles;
	Particle* _baseParticle;


};