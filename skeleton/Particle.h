#pragma once
#include <PxPhysicsAPI.h>
#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

class Particle
{
public:
	Particle(Vector3 pos, Vector3 v, Vector3 a, Vector4 c, double d = 0, float ml = -1, float dY = 0);
	Particle(){};
	~Particle();
	void integrate(double t);
	bool isDead() { return _kill; }
	virtual Particle* clone() const { return new Particle(*this); }
protected:
	void init(Vector3 pos);
	Vector3 _vel;
	Vector3 _acceleration;
	double _damping;
	float _mass;
	Transform _transform;
	RenderItem* _renderItem;
	Vector4 _color;
	float _maxLifetime;
	float _lifeTime = 0;
	float _limitY;
private:
	bool _kill = false;
};

