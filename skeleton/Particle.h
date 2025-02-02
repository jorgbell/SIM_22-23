#pragma once
#include <PxPhysicsAPI.h>
#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

class Particle
{
public:
	//constructor habitual (se puede llamar vacio para que haya valores por defecto para cambiar mas adelante)
	Particle(Vector3 pos = Vector3(0, 0, 0), Vector3 v = Vector3(0,0,0),
		Vector3 a = Vector3(0, 0, 0), Vector4 c = Vector4(1, 1, 1, 1),
		double d = 0.99, float ml = -1, float dY = 0, float mass = 1e6, physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0)));
	~Particle();
	//virtual void init(Vector3 pos, Vector3 v, Vector3 a, Vector4 c, double d = 1, float ml = -1, float dY = 0, float mass = 1.0);
	virtual void integrate(double t);
	virtual Particle* clone() const {
		auto p = new Particle(*this);
		p->initRenderItem();
		return p;
	}
	void DeregisterParticle();
	//Clears accumulated force
	void clearForce();
	//Add force to apply in next integration only
	void addForce(const Vector3& f);

	//SETTERS
	void setPos(Vector3 p) { _transform = Transform(p); }
	void setVel(Vector3 v) { _vel = v; }
	void setAcc(Vector3 a) { _acceleration = a; }
	void setDamp(double d) {	//clamp del damping
		if (_damping < 0) _damping = 0;
		else if (_damping > 1) _damping = 1;
		_damping = d;
	}
	void setMass(float m) { _mass = m; }
	void setColor(Vector4 c) { _color = c; DeregisterParticle(); initRenderItem(); }
	void setmaxLifeTime(float l) { _maxLifetime = l; }
	void setGroundLimit(float l) { _limitY = l; }
	void setDead(bool b) { _kill = b; }
	void setShape(physx::PxShape* s);
	//GETTERS
	Vector3 getPos() { return _transform.p; }
	Vector3 getVel() { return _vel; }
	Vector3 getAcc() { return _acceleration; }
	double getDamp() { return _damping; }
	float getMass() { return _mass; }
	float getInverseMass() { return 1 / _mass; }
	Vector4 getColor() { return _color; }
	float getMaxLifeTime() { return _maxLifetime; }
	float getActualLifeTime() { return _lifeTime; }
	float getGroundLimit() { return _limitY; }
	bool isDead() { return _kill; }
protected:
	virtual void initRenderItem();
	physx::PxShape* _shape;

	Vector3 _vel;
	Vector3 _acceleration;
	double _damping;
	float _mass;
	Transform _transform;
	RenderItem* _renderItem = nullptr;
	Vector4 _color;
	float _maxLifetime;
	float _lifeTime = 0;
	float _limitY;

	//Accumulated force
	Vector3 force;
private:
	bool _kill = false;
};

