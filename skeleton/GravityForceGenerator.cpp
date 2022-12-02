#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(const Vector3& g)
{
	setGravity(g);
}

void GravityForceGenerator::updateForce(Particle* particle, double t)
{

	//Check that the particle has Finite mass
	if (fabs(particle->getInverseMass()) < 1e-10)
		return;

	//Apply the mass scaled gravity
	particle->addForce(_gravity);

}
