#include "Shotgun.h"

Shotgun::Shotgun(physx::PxPhysics *gp, Camera* cam, bool* shoot, double radius, int nVertex)
	:RBShootGenerator("Shotgun", gp,cam, { 3,-2,-5 },shoot,
		/*pos(null)*/{0,0,0}, /*vel*/{0,0,100}, /*avel*/{0,0,0},/*color*/{0.5, 1, 0.5, 1},
		/*cooldown*/2,/*timebetween*/0,/*nbalas*/1,/*numBalas,null*/nVertex,1,
		/*masa*/3.0, /*dump*/0.95, /*adamp*/0.1, /*lifetime*/3),
	_radius(radius)
{}

list<DynamicRigidBody*> Shotgun::shoot() {
	//Este método disparará tres balas al mismo tiempo, formando un triángulo

	list<DynamicRigidBody*> rbs;
	//la velocidad sera la misma para todas las balas
	Vector3 dir = _cam->getDir();
	Vector3 vel = _velMedia.z * dir;	 //modificamos una copia, no el vector de velocidad original

	//forma igual para todas las balas
	SHAPE s; s.type = sphere;  s.sphere = { 0.6 };

	//cambiaremos la posicion inicial de la bala formando una circunferencia
	Vector3 origin = _cam->getEye() + offset_To_Origin;
	double startX = 0.0 - _radius; double startY = 0.0;
	// Calculate the angle we'll need to rotate by for each iteration (* (PI / 180) to convert it into radians)
	double segRotationAngle = (360.0 / _nRigidBodies) * (3.14159265 / 180);
	for (int i = 0; i < _nRigidBodies; i++) {
		double finalSegRotationAngle = (i * segRotationAngle);
		Vector3 newPos = {
			 (float)(cos(finalSegRotationAngle) * startX - sin(finalSegRotationAngle) * startY),
			 (float)(cos(finalSegRotationAngle) * startY + sin(finalSegRotationAngle) * startX),
			 origin.z
		};
		// Set the point relative to our defined center (in this case the center of the screen)
		newPos.x += origin.x;
		newPos.y += origin.y;

		DynamicRigidBody* rb = new DynamicRigidBody(
			s,
			newPos,
			_color,
			vel,
			_avelmedia,
			_ldamp,
			_adamp,
			_mass,
			_lifetime_media,
			0.0F
		);
		rb->Init(gphysics);
		rbs.push_back(rb);
	}

	return rbs;
}