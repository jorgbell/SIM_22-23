#include "WhirlwindRBFG.h"

WhirlwindRBFG::WhirlwindRBFG(const Vector3& windPos, double windRadius, const Vector4& color, float k1, float k2) :
	WindRBFG({ 0,0,0 }, windPos, windRadius, color, k1, k2)
{

}

void WhirlwindRBFG::updateForce(DynamicRigidBody* rb, double t)
{
	//Check that the particle has Finite mass
	if (fabs(rb->getInverseMass()) < 1e-10 || !collides(rb->getPos()))
		return;
	Vector3 p = rb->getPos();
	Vector3 center = regionTransform.p;
	float x = (p.z - center.z) * -1;
	float y = 50 - (p.y - center.y);
	float z = p.x - center.x;
	Vector3 torbellinoForce = Vector3(x, y, z);
	torbellinoForce *= _k1;

	rb->addForce(torbellinoForce);

}
