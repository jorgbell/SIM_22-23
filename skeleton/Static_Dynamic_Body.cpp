#include "Static_Dynamic_Body.h"

StaticRigidBody::StaticRigidBody(PxPhysics* gphysics, Vector3 p, Vector4 c, SHAPE shapeInfo) :
	pos(p), color(c), pxshapeInfo(shapeInfo) 
{
	rigidStatic = gphysics->createRigidStatic({ pos.x,pos.y, pos.z });
	switch (pxshapeInfo.type) {
	case box:
		shape = CreateShape(PxBoxGeometry(pxshapeInfo.box.hx, pxshapeInfo.box.hy, pxshapeInfo.box.hz));
		break;
	case sphere:
		shape = CreateShape(PxSphereGeometry(pxshapeInfo.sphere.ir));
		break;
	default:
		break;
	}
	rigidStatic->attachShape(*shape);
	RI = new RenderItem(shape, rigidStatic, color);
}

StaticRigidBody::~StaticRigidBody() {
	shape->release();
	RI->release();
}


DynamicRigidBody::DynamicRigidBody(PxPhysics* gphysics, Vector3 p, Vector4 c, SHAPE shapeInfo) :
	pos(p), color(c), pxshapeInfo(shapeInfo)
{
	rigidDynamic = gphysics->createRigidDynamic({ pos.x,pos.y, pos.z });
	switch (pxshapeInfo.type) {
	case box:
		shape = CreateShape(PxBoxGeometry(pxshapeInfo.box.hx, pxshapeInfo.box.hy, pxshapeInfo.box.hz));
		break;
	case sphere:
		shape = CreateShape(PxSphereGeometry(pxshapeInfo.sphere.ir));
		break;
	default:
		break;
	}
	rigidDynamic->attachShape(*shape);
	RI = new RenderItem(shape, rigidDynamic, color);
}

DynamicRigidBody::~DynamicRigidBody() {
	shape->release();
	RI->release();
}