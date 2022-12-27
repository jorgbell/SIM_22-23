#include "NailGun.h"

list<DynamicRigidBody*> NailGun::shoot() {

	list<DynamicRigidBody*> rbs;

	Vector3 origin = GetCamera()->getEye() + GetCamera()->getDir().getNormalized() * 2;
	origin.x -= (_nRigidBodies-1 * _distance);
	Vector3 vel = _force * GetCamera()->getDir();

	SHAPE s; s.type = sphere;  s.sphere = { 0.4 };
	for (int i = 0; i < _nRigidBodies; i++) {
		origin.x += i * _distance;
		DynamicRigidBody* rb = new DynamicRigidBody(
			_name.c_str(),
			s,
			origin,
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