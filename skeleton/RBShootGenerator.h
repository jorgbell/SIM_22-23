#pragma once
#include "RBGenerator.h"

class RBShootGenerator : public RBGenerator {
public:
	RBShootGenerator(string Name, PxPhysics* gphy, Camera* cam, Vector3 offsetToOrigin, bool* shoot,
		Vector3 pos, Vector3 vel, Vector3 avel, Vector4 color = { 1,1,1,1 }, 
		int n = 1, int mRB = 10, double mass = 1,double ldamp = 0.99, double adamp = 0.05,
		double lifetime = -1, double prob = 1.0):
	RBGenerator(Name, gphy, pos, vel, avel, color, n, mRB, mass, ldamp, adamp, lifetime, prob),
		_cam(cam),canShoot(shoot), offset_To_Origin(offsetToOrigin){};
	list<DynamicRigidBody*> generateParticles();
private:
	bool* canShoot;
	Vector3 offset_To_Origin;
	Camera* _cam;
};