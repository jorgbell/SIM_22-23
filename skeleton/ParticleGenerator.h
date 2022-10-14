#pragma once
#include "Particle.h"
#include <list>
using namespace std;

class ParticleGenerator {
public:
	ParticleGenerator(Vector3 pos, Vector3 vel, int n, Particle* b, string t = to_string(generatorID++)) :
		_origin(pos), _velMedia(vel), _nParticles(n), _baseParticle(b), _name(t), _probability(1.0)
	{}

	void setBaseParticle(Particle* model) { _baseParticle = model; }

	virtual list<Particle*> generateParticles() = 0;
	string getGeneratorName() { return _name; }

protected:
	string _name;
	Vector3 _origin;
	Vector3 _velMedia;
	double _probability;
	int _nParticles;
	Particle* _baseParticle;


};