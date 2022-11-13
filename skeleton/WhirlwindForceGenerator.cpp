#include "WhirlwindForceGenerator.h"

WhirlwindForceGenerator::WhirlwindForceGenerator(const Vector3& windPos, double windRadius, const Vector4& color, float k1, float k2) :
	WindForceGenerator({0,0,0}, windPos, windRadius, color, k1, k2)
{

}

void WhirlwindForceGenerator::updateForce(Particle* particle, double t)
{
	//Check that the particle has Finite mass
	if (fabs(particle->getInverseMass()) < 1e-10 || !collides(particle->getPos()))
		return;
	Vector3 p = particle->getPos();
	Vector3 center = regionTransform.p;
	float x = (p.z - center.z) * -1;
	float y = 50- (p.y - center.y);
	float z = p.x - center.x;
	Vector3 torbellinoForce = Vector3(x, y, z);
	torbellinoForce *= _k1;

	particle->addForce(torbellinoForce * particle->getMass());

}
