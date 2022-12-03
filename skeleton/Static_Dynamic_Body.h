#pragma once
#include "RenderUtils.hpp"
using namespace physx;
using namespace std;

enum TYPESHAPE {
	box, sphere, capsule
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
};

class RigidBody {
public:
	RigidBody(SHAPE info, Vector3 p = {0,0,0}, Vector4 c = {1,1,1,1}, float mL = -1, float limY = 0);
	~RigidBody();

protected:
	PxShape* shape;
	RenderItem* RI;
	SHAPE pxshapeInfo;

	Vector3 pos;
	Vector4 color;
	float lifeTime, maxLifeTime, limitY;
	bool kill = false;

};

class StaticRigidBody : RigidBody {
public:
	StaticRigidBody(PxPhysics* gphysics, SHAPE shapeInfo, Vector3 p = { 0,0,0 }, Vector4 c = { 1,1,1,1 }, float mL = -1, float limY = 0);
	~StaticRigidBody();
	PxRigidStatic* _rigidStatic() { return rigidStatic; };

private:
	PxRigidStatic* rigidStatic;
};

class DynamicRigidBody : RigidBody {
public:
	DynamicRigidBody(PxPhysics* gphysics, SHAPE shapeInfo, Vector3 lVel = { 0,0,0 }, Vector3 aVel = { 0,0,0 },
		double ldamp = 0.99, double adamp = 0.05, double mass = 5,
		Vector3 p = { 0,0,0 }, Vector4 c = { 1,1,1,1 }, float mL = -1, float limY = 0);
	~DynamicRigidBody();
	PxRigidDynamic* _rigidDynamic() { return rigidDynamic; }
	bool isDead() { return kill; }
	void update(double t);

private:
	PxRigidDynamic* rigidDynamic;
	double linearDamping, angularDamping, mass;

	Vector3 linearVel, angularVel;
	Vector3 force, torque = {0,0,0};

};
