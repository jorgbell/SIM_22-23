#include "Scene.h"


Scene::Scene(PxFoundation* gF, PxPvd* gP, std::string name) : 
	gFoundation(gF), gPvd(gP), id(name)
{
	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);
	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	Init();
}

void Scene::Init() {

}

void Scene::Release()
{
}

void Scene::update(double t)
{
	;
}

void Scene::stepPhysics(bool interactive, double t)
{
	gScene->simulate(t);
	gScene->fetchResults(true);
}

void Scene::cleanupPhysics(bool interactive)
{
	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	gFoundation->release();
}

void Scene::keyPress(unsigned char key)
{
	switch (toupper(key))
	{
	default:
		break;
	}
}

void Scene::onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
}
