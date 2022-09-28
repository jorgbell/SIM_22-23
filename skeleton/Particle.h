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
	Particle(){};
	~Particle();
	void integrate(double t);
protected:
	Vector3 _vel;
	Vector3 _acceleration;
	double _damping;
	float _mass;
	Transform _transform;
	RenderItem* _renderItem;
	Vector4 _color;

};

