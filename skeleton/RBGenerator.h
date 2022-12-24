#pragma once
#include "Static_Dynamic_Body.h"
#include "RBForceGenerator.h"
#include <string>
#include <list>
using namespace std;

class RBGenerator {
public:
	RBGenerator(string Name, PxPhysics* gphy, Vector3 pos, Vector3 lvel, Vector3 avel, 
		Vector4 color = {1,1,1,1}, int n = 10, int mRB = 100, double mass = 1, double ldamp = 0.99, double adamp = 0.05,
		double lifetime = -1, double prob = 1.0) :
		gphysics(gphy), _origin(pos), _velMedia(lvel), _nRigidBodies(n), _maxRigidBodies(mRB), 
		_name(Name), _probability(prob), _lifetime_media(lifetime), _color(color), _mass(mass), _avelmedia(avel),
		_ldamp(ldamp), _adamp(adamp)
	{
	}

	virtual list<DynamicRigidBody*> generateParticles() = 0;
	string getParticleGeneratorName() { return _name; }

	void addForceGenerator(RBForceGenerator* fg) {
		_forceGeneratorsPool.push_back(fg);
	}
	void eraseForceGenerator(string name) {
		bool encontrado = false;
		list<RBForceGenerator*>::iterator it = _forceGeneratorsPool.begin();
		RBForceGenerator* fg;

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

	list<RBForceGenerator*> getForceGenerators() { return _forceGeneratorsPool; }

	virtual void update(double t) = 0 {};
protected:
	string _name;
	Vector3 _origin;
	Vector3 _velMedia, _avelmedia;
	double _mass;
	double _probability;
	double _lifetime_media;
	int _nRigidBodies;
	int _maxRigidBodies;
	list<RBForceGenerator*> _forceGeneratorsPool;
	Vector4 _color;
	PxPhysics* gphysics;
	double _ldamp, _adamp;


};