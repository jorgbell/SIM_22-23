#include "RBShootGenerator.h"

list<DynamicRigidBody*> RBShootGenerator::generateParticles() {
	list<DynamicRigidBody*> rbs;

	/* si no ha disparado, devuelve una lista vacia*/
	if (!(*canShoot))
		return rbs;

	//como maximo creara nParticles, según la probabilidad dada
	for (int i = 0; i < _nRigidBodies; i++) {
		int r = rand() % 100;
		if (_probability * 100 >= r) {
			//genera una particula
			DynamicRigidBody* rb = new DynamicRigidBody(gphysics);
			//siguiente valor de velocidad y posicion origen segun la distribucion gaussiana
			Vector3 newPos = _origin + offset_To_Origin;
			rb->setPos(newPos); rb->setLinearVel(_velMedia); rb->setAngularVel(_avelmedia); 
			rb->setLinearDamping(_ldamp); rb->setAngularDamping(_adamp);
			rb->setMaxLifeTime(_lifetime_media); rb->setMass(_mass);

			SHAPE s = SHAPE(TYPESHAPE::sphere); s.sphere = { 5 };
			rb->createshape(s);
			rb->Init(gphysics);
			rb->changeColor(_color);

			rbs.push_back(rb);
		}
	}

	return rbs;
};
