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
			Vector3 newPos = _cam->getEye() + offset_To_Origin;
			Vector3 dir = _cam->getDir();
			if (!dir.isNormalized()) {
				dir.normalize();
			}
			Vector3 newVel = dir * 50.0f;
			SHAPE s; s.type = sphere;  s.sphere = { 0.4 };

			DynamicRigidBody* rb = new DynamicRigidBody(
				s,
				newPos,
				_color,
				newVel,
				_avelmedia,
				_ldamp,
				_adamp,
				_mass,
				-1.0f,
				0.0F
			);
			rb->Init(gphysics);
			rbs.push_back(rb);
		}
	}

	return rbs;
};
