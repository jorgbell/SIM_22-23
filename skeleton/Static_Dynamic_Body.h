#pragma once
#include "RenderUtils.hpp"
using namespace physx;
using namespace std;

enum TYPESHAPE {
	box, sphere, capsule, none
};
struct BOX {
	PxReal hx;
	PxReal hy;
	PxReal hz;
};
struct SPHERE {
	PxReal ir;
};
struct CAPSULE {
	PxReal radius;
	PxReal halfHeight;
};
struct SHAPE {
	TYPESHAPE type;
	union {
		BOX box;
		SPHERE sphere;
		CAPSULE capsule;
	};

	SHAPE(TYPESHAPE t) { type = type; }
};

class RigidBody {
public:
	RigidBody(SHAPE info = SHAPE(TYPESHAPE::none), Vector3 p = {0,0,0}, Vector4 c = {1,1,1,1}, float mL = -1, float limY = 0);
	~RigidBody();
	virtual void createshape(SHAPE info);
	virtual bool Init(PxPhysics* gphysics) = 0;
	virtual void changeColor(Vector4 c) = 0;

	//++++++++++++++++SETTERS++++++++++++++++++++++
	virtual void setPos(Vector3 p) { pos = p; }
	virtual void setMaxLifeTime(float t) { maxLifeTime = t; }
	virtual void setLimitY(float y) { limitY = y; }
protected:
	PxShape* shape;
	RenderItem* RI;
	SHAPE pxshapeInfo;

	Vector3 pos;
	Vector4 color;
	float lifeTime = 0; float maxLifeTime, limitY;
	bool kill = false;

};

class StaticRigidBody : RigidBody {
public:
	StaticRigidBody(PxPhysics* gphysics, SHAPE shapeInfo, Vector3 p = { 0,0,0 }, Vector4 c = { 1,1,1,1 }, float mL = -1, float limY = 0);
	~StaticRigidBody();
	PxRigidStatic* _rigidStatic() { return rigidStatic; };
	virtual void createshape(SHAPE info) { RigidBody::createshape(info); }
	virtual bool Init(PxPhysics* gphysics) override;
	virtual void changeColor(Vector4 c) override;

	virtual void setPos(Vector3 p) { RigidBody::setPos(p); }
	virtual void setMaxLifeTime(float t) { RigidBody::setMaxLifeTime(t); }
	virtual void setLimitY(float y) { RigidBody::setLimitY(y); }
private:
	PxRigidStatic* rigidStatic;
};

class DynamicRigidBody : RigidBody {
public:
	DynamicRigidBody(PxPhysics* gphysics, SHAPE shapeInfo = SHAPE(TYPESHAPE::none), Vector3 lVel = {0,0,0}, Vector3 aVel = {0,0,0},
		double ldamp = 0.99, double adamp = 0.05, double mass = 5,
		Vector3 p = { 0,0,0 }, Vector4 c = { 1,1,1,1 }, float mL = -1, float limY = 0);
	~DynamicRigidBody();
	PxRigidDynamic* _rigidDynamic() { return rigidDynamic; }
	virtual void createshape(SHAPE info) { RigidBody::createshape(info); }
	virtual bool Init(PxPhysics* gphysics) override;
	virtual void changeColor(Vector4 c) override;

	virtual void setPos(Vector3 p) { RigidBody::setPos(p); }
	virtual void setMaxLifeTime(float t) { RigidBody::setMaxLifeTime(t); }
	virtual void setLimitY(float y) { RigidBody::setLimitY(y); }
	bool isDead() { return kill; }
	void update(double t);

	//++++++++++++++++++++++SETTERS++++++++++++++++++
	void setLinearDamping(double ld) { linearDamping = ld; }
	void setAngularDamping(double ad) { angularDamping = ad; }
	void setMass(double m) { mass = m; }
	void setLinearVel(Vector3 lv) { linearVel = lv; }
	void setAngularVel(Vector3 av) { angularVel = av; }
	void addForce(Vector3 f) { force += f; }
	void addTorque(Vector3 t) { torque += t; }
private:
	PxRigidDynamic* rigidDynamic;
	double linearDamping, angularDamping, mass;

	Vector3 linearVel, angularVel;
	Vector3 force, torque = {0,0,0};

};
