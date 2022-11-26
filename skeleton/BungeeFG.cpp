#include "BungeeFG.h"

void BungeeFG::updateForce(Particle* particle, double t) {
	Vector3 f = particle->getPos();
	f -= _other->getPos();

	// Length
	float length = f.normalize();
	length = (length - _resting_length);
	if (length <= 0.0f)
		return;

	// Resulting force
	f *= -(length * _k);

	particle->addForce(f*particle->getMass());
}