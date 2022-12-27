#include "Static_Dynamic_Body.h"
#include <iostream>
RigidBody::RigidBody(const char * id, SHAPE info, Vector3 p, Vector4 c, float mL, float limY) :
	pos(p), color(c),pxshapeInfo(info), maxLifeTime(mL), limitY(limY), RI(nullptr), name(id)
{
	createshape(info);
};
RigidBody::~RigidBody() {
	shape->release();
	RI->release();
}
void RigidBody::createshape(SHAPE info) {
	pxshapeInfo = info;
	switch (pxshapeInfo.type) {
	case box:
		shape = CreateShape(PxBoxGeometry(pxshapeInfo.box.hx, pxshapeInfo.box.hy, pxshapeInfo.box.hz));
		break;
	case sphere:
		shape = CreateShape(PxSphereGeometry(pxshapeInfo.sphere.ir));
		break;
	case capsule:
		shape = CreateShape(PxCapsuleGeometry(pxshapeInfo.capsule.radius, pxshapeInfo.capsule.halfHeight));
		break;
	case none:
		shape = nullptr;
		break;
	}
}

StaticRigidBody::StaticRigidBody(const char* id, SHAPE shapeInfo, Vector3 p, Vector4 c, float mL, float limY) :
	RigidBody(id, shapeInfo, p, c, mL, limY)
{
}

StaticRigidBody::~StaticRigidBody() {
	;
}

bool StaticRigidBody::Init(PxPhysics* gphysics) {
	if (shape == nullptr) {
		std::cout << "FORMA NO INICIALIZADA\n";
		return false;
	}

	rigidStatic = gphysics->createRigidStatic({ pos.x,pos.y, pos.z });
	rigidStatic->setName(name);
	const char* n = rigidStatic->getName();
	rigidStatic->attachShape(*shape);
	changeColor(color);
}

void StaticRigidBody::changeColor(Vector4 c) {
	color = c;
	if (RI != nullptr) {
		DeregisterRenderItem(RI);
		delete RI;
		RI = nullptr;
	}
	RI = new RenderItem(shape, rigidStatic, color);
}


DynamicRigidBody::DynamicRigidBody(const char* id, SHAPE shapeInfo, Vector3 p ,Vector4 c ,
	Vector3 lVel , Vector3 aVel, double ldamp ,double adamp,double m,
	float mL, float limY):
	RigidBody(id, shapeInfo, p, c, mL, limY), linearVel(lVel), angularVel(aVel), linearDamping(ldamp), angularDamping(adamp), mass(m)
{
}

DynamicRigidBody::~DynamicRigidBody() {
	;
}


bool DynamicRigidBody::Init(PxPhysics* gphysics) {
	if (shape == nullptr) {
		std::cout << "FORMA NO INICIALIZADA\n";
		return false;
	}

	rigidDynamic = gphysics->createRigidDynamic({ pos.x,pos.y, pos.z });
	rigidDynamic->attachShape(*shape);
	rigidDynamic->setName(name);
	//PxRigidBodyExt::updateMassAndInertia(*rigidDynamic, 1);
	rigidDynamic->setLinearVelocity(linearVel);
	rigidDynamic->setAngularVelocity(angularVel);
	rigidDynamic->setLinearDamping(linearDamping);
	rigidDynamic->setAngularDamping(angularDamping);
	rigidDynamic->setMass(mass);
	rigidDynamic->setMassSpaceInertiaTensor({ 0.f,0.f,1.f });

	changeColor(color);

}

void DynamicRigidBody::changeColor(Vector4 c) {
	color = c;
	if (RI != nullptr) {
		DeregisterRenderItem(RI);
		delete RI;
		RI = nullptr;
	}
	RI = new RenderItem(shape, rigidDynamic, color);
}


void DynamicRigidBody::update(double t) {

	lifeTime += t;
	if ((maxLifeTime > 0 && lifeTime > maxLifeTime) || rigidDynamic->getGlobalPose().p.y < limitY)
		kill = true;
}
