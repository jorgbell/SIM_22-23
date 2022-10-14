#include "Particle.h"

Particle::Particle(Vector3 pos, Vector3 v, Vector3 a,Vector4 c, double d, float l, float lim) : _vel(v), _acceleration(a), _damping(d), _color(c), _maxLifetime(l), _limitY(lim)
{
	init(pos);
}

Particle::~Particle()
{
	DeregisterRenderItem(_renderItem);
}

void Particle::integrate(double t)
{
	_vel += _acceleration * t;
	_vel *= powf(_damping, t);
	_transform.p += _vel * t;
	_lifeTime += t;

	if (_maxLifetime > 0 && _lifeTime > _maxLifetime || _transform.p.y < _limitY)
		_kill = true;

}

void Particle::init(Vector3 pos)
{
	_transform = Transform(pos);
	_renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(1.0)), &_transform, _color);
	//clamp del damping
	if (_damping < 0) _damping = 0;
	else if (_damping > 1) _damping = 1;
}
