#include "Static_Dynamic_Body.h"

RigidBody::RigidBody(SHAPE info, Vector3 p, Vector4 c, float mL, float limY) :
	pos(p), color(c), pxshapeInfo(info), maxLifeTime(mL), limitY(limY)
{
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
};
RigidBody::~RigidBody() {
	shape->release();
	RI->release();
}

StaticRigidBody::StaticRigidBody(PxPhysics* gphysics, SHAPE shapeInfo, Vector3 p, Vector4 c, float mL, float limY) :
	RigidBody(shapeInfo, p, c, mL, limY)
{
	rigidStatic = gphysics->createRigidStatic({ pos.x,pos.y, pos.z });
	rigidStatic->attachShape(*shape);
	RI = new RenderItem(shape, rigidStatic, color);
}

StaticRigidBody::~StaticRigidBody() {
	;
}


DynamicRigidBody::DynamicRigidBody(PxPhysics* gphysics, SHAPE shapeInfo, Vector3 lVel, Vector3 aVel,
	double ldamp, double adamp, double m ,
	Vector3 p, Vector4 c, float mL, float limY) :
	RigidBody(shapeInfo, p, c, mL, limY), linearVel(lVel), angularVel(aVel), linearDamping(ldamp), angularDamping(adamp), mass(m)
{
	rigidDynamic = gphysics->createRigidDynamic({ pos.x,pos.y, pos.z });
	rigidDynamic->attachShape(*shape);
	RI = new RenderItem(shape, rigidDynamic, color);

	//PxRigidBodyExt::updateMassAndInertia(*rigidDynamic, 1);
	rigidDynamic->setLinearVelocity(linearVel); rigidDynamic->setAngularVelocity(angularVel);
	rigidDynamic->setLinearDamping(linearDamping); rigidDynamic->setAngularDamping(angularDamping);
	rigidDynamic->setMass(mass);
	rigidDynamic->setMassSpaceInertiaTensor({ 0.f,0.f,1.f });

}

DynamicRigidBody::~DynamicRigidBody() {
	;
}

void DynamicRigidBody::update(double t) {
	lifeTime += t;
	if ((maxLifeTime > 0 && lifeTime > maxLifeTime) || rigidDynamic->getGlobalPose().p.y < limitY)
		kill = true;
}
