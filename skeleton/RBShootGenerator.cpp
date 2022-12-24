#include "RBShootGenerator.h"

list<DynamicRigidBody*> RBShootGenerator::generateParticles() {
	list<DynamicRigidBody*> rbs;
	/* si no ha disparado O no ha pasado el tiempo suficiente desde el ultimo disparo, devuelve una lista vacia*/
	if (!(*isShooting))
		return rbs;
	if (actualCooldown <= _COOLDOWN) {
		(*isShooting) = false;
		return rbs;
	}
	//dispara la rafaga si el tiempo que ha pasado desde la ultima es el suficiente
	if (tiempoRafaga <= _TIME_BETWEEN_SHOOTS)
		return rbs;
	
	//SE PRODUCE UN DISPARO
		//comprueba si ha disparado el numero de rafagas totales, para dejar de disparar
	nShoots++;
	if (nShoots >= _NUM_RAFAGAS) {
		(*isShooting) = false;
		nShoots = 0;
		//empieza a contar el cooldown hasta el siguiente disparo
		actualCooldown = 0;
	}
	tiempoRafaga = 0;
	return shoot();
};


void RBShootGenerator::update(double t) {

	//se les suma el tiempo que ha pasado desde el ultimo frame
	tiempoRafaga += t;
	if (!(*isShooting))
		actualCooldown += t;
}

list<DynamicRigidBody*> RBShootGenerator::shoot() {

	list<DynamicRigidBody*> rbs;
	//Creara un solo rb, porque cuando dispara debe salir y contar el tiempo para saber si puede seguir disparando
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
	return rbs;
}