#include "Particle.h"

Particle::Particle(Vector3 pos, Vector3 v, Vector3 a,Vector4 c, double d = 0.5) : _vel(v), _acceleration(a), _dumping(d), _color(c)
{
	_transform = Transform(pos);
	_renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(1.0)), &_transform, _color);
}

Particle::~Particle()
{
	DeregisterRenderItem(_renderItem);
}

void Particle::integrate(double t)
{
	double x = _transform.p.x + _vel.x * t;
	double y = _transform.p.y + _vel.y * t;
	double z = _transform.p.z + _vel.z * t;
	_transform = Transform(x, y, z);
}
