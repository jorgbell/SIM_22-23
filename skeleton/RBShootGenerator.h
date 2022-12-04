#pragma once
#include "RBGenerator.h"

class RBShootGenerator : RBGenerator {
public:
	RBShootGenerator(string Name, PxPhysics* gphy, Vector3 offsetToOrigin, bool* shoot,
		Vector3 pos, Vector3 vel, Vector4 color = { 1,1,1,1 }, 
		int n = 10, int mRB = 100, double mass = 1, double lifetime = -1, double prob = 1.0):
	RBGenerator(Name, gphy, pos, vel, color, n, mRB, mass, lifetime, prob), canShoot(shoot), offset_To_Origin(offsetToOrigin){};
	list<DynamicRigidBody*> generateParticles();
private:
	bool* canShoot;
	Vector3 offset_To_Origin;
};