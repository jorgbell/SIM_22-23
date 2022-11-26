#include "AnchoredSpringFG.h"

AnchoredSpringFG::AnchoredSpringFG(double k, double resting, const Vector3& anchor_pos)
	:SpringForceGenerator(k, resting, nullptr)
{
	_other = new Particle(anchor_pos, {0,0,0},{0,0,0});
	_other->setMass(1e6);
	_other->setShape(CreateShape(physx::PxBoxGeometry(3,3,3)));
}
	
AnchoredSpringFG::~AnchoredSpringFG()
{
	delete _other;
}

