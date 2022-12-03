#pragma once
#include "RenderUtils.hpp"
using namespace physx;
using namespace std;

enum TYPESHAPE {
	box,sphere
};

struct BOX {
	PxReal hx;
	PxReal hy;
	PxReal hz;
};
struct SPHERE {
	PxReal ir;
};

struct SHAPE {
	TYPESHAPE type;
	union {
		BOX box;
		SPHERE sphere;
	};
};

class StaticRigidBody {
public:
	StaticRigidBody(PxPhysics* gphysics, Vector3 pos, Vector4 color, SHAPE shapeInfo);
	~StaticRigidBody();
	PxRigidStatic* _rigidStatic() { return rigidStatic; };

private:
	PxRigidStatic* rigidStatic;
	PxShape* shape;
	RenderItem* RI;
	Vector3 pos;
	Vector4 color;
	SHAPE pxshapeInfo;
};

class DynamicRigidBody {
public:
	DynamicRigidBody(PxPhysics* gphysics, Vector3 pos, Vector4 color, SHAPE shapeInfo);
	~DynamicRigidBody();
	PxRigidDynamic* _rigidDynamic(){return rigidDynamic;}

private:
	PxRigidDynamic* rigidDynamic;
	PxShape* shape;
	RenderItem* RI;
	double deathTime, lifetime;
	Vector3 pos, force, torque;
	Vector4 color;
	SHAPE pxshapeInfo;


};
