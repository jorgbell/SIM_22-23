#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(const Vector3& g)
{
}

void GravityForceGenerator::updateForce(Particle* particle, double t)
{

	//Check that the particle has Finite mass
	//if (fabs(particle->_inv_mass) < 1e-10)
	//	return;

	////Apply the mass scaled gravity
	//particle->addForce(_gravity * particle->_mass);

}
