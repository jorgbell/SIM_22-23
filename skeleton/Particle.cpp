#include "Particle.h"
#include <iostream>
Particle::Particle(Vector3 pos, Vector3 v, Vector3 a,Vector4 c, double d, float l, float lim, float mass, Shape geometry) :
 _vel(v), _acceleration(a), _damping(d), _color(c), _maxLifetime(l), _limitY(lim), _mass(mass), _geometry (geometry)
{
	setPos(pos);
	setGeometry(_geometry);
	initRenderItem();
	force = Vector3(0, 0, 0);
}

Particle::~Particle()
{
	DeregisterParticle();
}

void Particle::DeregisterParticle() {
	if (_renderItem == nullptr)
		return;
	DeregisterRenderItem(_renderItem);
	delete _renderItem;
	_renderItem = nullptr;
}

void Particle::clearForce()
{
	force *= 0;
}

void Particle::addForce(const Vector3& f)
{
	force += f;
}

void Particle::integrate(double t)
{
	
#pragma region Practica_2
	/*_vel += _acceleration * t;
	_vel *= powf(_damping, t);
	_transform.p += _vel * t;
	_lifeTime += t;*/
#pragma endregion
#pragma region Practica_3
	//Trivial case, inifinite mass --> do nothing
	if (getInverseMass() <= 0.0f)
		return;
	_transform.p += _vel * t;
	Vector3 totalAcceleration = _acceleration;
	totalAcceleration += force * getInverseMass();

	//update linear velocity
	_vel += totalAcceleration * t;

	//impose drag (damping)
	_vel *= powf(_damping, t);

	clearForce();
	_lifeTime += t;
#pragma endregion

	if ((_maxLifetime > 0 && _lifeTime > _maxLifetime) || _transform.p.y < _limitY)
		_kill = true;

}

//s�lo se llamara de manera privada para evitar descontrol de memoria
void Particle::initRenderItem()
{
	switch (_geometry) {
	case BOX:
		_renderItem = new RenderItem(CreateShape(physx::PxBoxGeometry()), &_transform, _color);
		break;
	case SPHERE:
		_renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(1.0)), &_transform, _color);
		break;
	}
}
