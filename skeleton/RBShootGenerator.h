#pragma once
#include "RBGenerator.h"

class RBShootGenerator : public RBGenerator {
public:
	RBShootGenerator(string Name, PxPhysics* gphy, Camera* cam, Vector3 offsetToOrigin, bool* shotgunBool,	
		Vector3 pos, Vector3 vel, Vector3 avel, Vector4 color = { 1,1,1,1 }, 
		//parametros para la cadencia
		float cooldown = -1, float shootTime = 300, int nShoots = 1, 
		int n = 1, int mRB = 10, double mass = 1,double ldamp = 0.99, double adamp = 0.05,
		double lifetime = -1, double prob = 1.0):
	RBGenerator(Name, gphy, pos, vel, avel, color, n, mRB, mass, ldamp, adamp, lifetime, prob),
		_cam(cam),isShooting(shotgunBool), offset_To_Origin(offsetToOrigin), 
		_COOLDOWN(cooldown), _TIME_BETWEEN_SHOOTS(shootTime) , _NUM_RAFAGAS(nShoots) {};
	
	list<DynamicRigidBody*> generateParticles();

	virtual void update(double t);
protected:
	virtual list<DynamicRigidBody*> shoot();
	bool* isShooting;
	Vector3 offset_To_Origin;
	Camera* _cam;
	float _COOLDOWN, actualCooldown = 0;
	float _TIME_BETWEEN_SHOOTS, tiempoRafaga = 0;
	int _NUM_RAFAGAS, nShoots = 0;
};