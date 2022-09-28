#pragma once
#include <PxPhysicsAPI.h>
#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

class Particle
{
public:
	Particle(Vector3 pos, Vector3 v, Vector3 a,Vector4 c, double d = 0);
	~Particle();
	void integrate(double t);
private:
	Vector3 _vel;
	Vector3 _acceleration;
	double _damping;
	Transform _transform;
	RenderItem* _renderItem;
	Vector4 _color;

};

