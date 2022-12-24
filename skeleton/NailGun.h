#pragma once
#include "RBShootGenerator.h"
class NailGun : public RBShootGenerator {
public:
	NailGun(physx::PxPhysics* gp, Camera* cam, bool* shoot, float force, int nBalas, float Distance)
		:RBShootGenerator("NailGun", gp, cam, {0,0,0}, shoot, 
			{0,0,0},/*vel*/{0,0,0}, {8,0,0}, {0.5,0.5,0.5,1},
			/*cooldown*/ 1,/*timeBetween*/ 0.2, /*nShoots*/ 3, nBalas,0,
			/*masa*/1,/*damp*/0.80,0.05,3),
		_distance(Distance), _force(force) {}
	

protected:
	virtual list<DynamicRigidBody*> shoot() override;
	float _distance;
	float _force;
};