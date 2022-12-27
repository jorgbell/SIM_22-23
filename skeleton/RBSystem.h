#pragma once
#include <list>
#include <string>
#include "Static_Dynamic_Body.h"
#include "RBGenerator.h"
#include "RBForceRegistry.h"
using namespace std;

//ParticleSystem es el sistema que guarda los distintos generadores que haya y todas las particulas que haya en el sistema.

class RBSystem {
public:
	RBSystem(PxScene* gScene) { _gScene = gScene; };
	~RBSystem();
	virtual void clean();
	virtual void clear();
	virtual void update(double t);
	RBGenerator* getParticleGenerator(string name);
	virtual void addParticleGenerator(RBGenerator* p) { _generatorsPool.push_back(p); }
	virtual void addToForceRegistry(RBForceGenerator* fg, DynamicRigidBody* p) {
		_rbForceRegistry.addRegistry(fg, p);
		if (!isInPool(p))
			addToParticlePool(p);
	}
	virtual void addToParticlePool(DynamicRigidBody* p) {
		_gScene->addActor(*p->_rigidDynamic());
		_rbPool.push_back(p);
	}
	virtual bool isInPool(DynamicRigidBody* p) { return (std::find(_rbPool.begin(), _rbPool.end(), p) != _rbPool.end()); }
	virtual void erase(string name);
	int getNumGenerators() { return _generatorsPool.size(); }
protected:
	list<DynamicRigidBody*> _rbPool;
	list<RBGenerator*> _generatorsPool;
	virtual void checkRB();
	RBForceRegistry _rbForceRegistry;
	PxScene* _gScene;
private:

};