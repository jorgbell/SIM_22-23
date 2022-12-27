#include "RadialShotGenerator.h"

RadialShotGenerator::RadialShotGenerator(std::string name, physx::PxPhysics *gp, Camera* cam, Vector4 color,
	bool* shoot, double radius,	int nVertex, float force, float cooldown, float timeBetween, int nDisparos, double mass, double damp, double life)
	:RBShootGenerator(name, gp,cam, { 3,-2,-5 },shoot,
		/*pos(null)*/{0,0,0}, /*vel*/{0,0,0}, /*avel*/{0,0,0},/*color*/color,
		/*cooldown*/cooldown,/*timebetween*/timeBetween,/*nbalas*/nDisparos,/*numBalas,null*/nVertex,1,
		/*masa*/mass, /*dump*/damp, /*adamp*/0.1, /*lifetime*/life),
	_radius(radius), _force(force)
{}

list<DynamicRigidBody*> RadialShotGenerator::shoot() {
	//Este método disparará tres balas al mismo tiempo, formando un triángulo

	list<DynamicRigidBody*> rbs;
	//la velocidad sera la misma para todas las balas
	Vector3 dir = _cam->getDir().getNormalized();
	Vector3 vel = _force * dir;	 //modificamos una copia, no el vector de velocidad original

	//forma igual para todas las balas
	SHAPE s; s.type = sphere;  s.sphere = { 0.6 };

	//cambiaremos la posicion inicial de la bala formando una circunferencia
	Vector3 origin = GetCamera()->getEye() + GetCamera()->getDir().getNormalized() * 2;

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
			_name.c_str(),
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