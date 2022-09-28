#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Particle.h"
#include "Projectile_Pistol.h"

#include <iostream>



using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation* gFoundation = NULL;
PxPhysics* gPhysics = NULL;


PxMaterial* gMaterial = NULL;

PxPvd* gPvd = NULL;

PxDefaultCpuDispatcher* gDispatcher = NULL;
PxScene* gScene = NULL;
ContactReportCallback gContactReportCallback;



//VARIABLES
//+++++++++++++++++++PRACTICA 1+++++++++++++++++++++++
#pragma region Practica_1
//Particle* _p;
std::vector<Projectile_Pistol*> pistol;
Projectile_Pistol* p;
int MAX_CURRENT_PROJECTILES = 20;
#pragma endregion


// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);


	//+++++++++++++++++PRACTICA 1++++++++++++++++++++++++++++
#pragma region Practica_1
	//_p = new Particle(Vector3(0, 0, 0), Vector3(1,8,1), Vector3(1,9,1), Vector4(0.5, 0.5, 0, 1), 0.5);

#pragma endregion


}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	//INTEGRATE SCENE OBJECTS
		//+++++++++++++PRACTICA 1+++++++++++++++++++++
#pragma region Practica_1
	//_p->integrate(t);
#pragma endregion

	gScene->simulate(t);
	gScene->fetchResults(true);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

#pragma region Practica_1
	//delete _p;
	for (auto p : pistol) {
		delete p;
	}
	pistol.clear();

#pragma endregion



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

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch (toupper(key))
	{
		//case 'B': break;
		//case ' ':	break;
	case 'P': 
		/*
			si llega al maximo generados definidos previamente, elimina el ultimo.
			hecho de manera previa al generador de particulas, lo ideal seria darles un tiempo de vida
		*/
		if (pistol.size() >= MAX_CURRENT_PROJECTILES) {
			auto a = pistol[pistol.size() - 1];
			pistol.pop_back();
			delete a;
		}
		//p = new Projectile_Pistol(GetCamera()->getEye(), GetCamera()->getDir(), Vector4(0.5, 0.5, 0, 1));
		pistol.push_back(new Projectile_Pistol(Vector3(0.0f, 1.5f, 0.0), Vector3(0,1,0), Vector4(0.5, 0.5, 0, 1)));
	case ' ':
		break;
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char* const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for (PxU32 i = 0; i < frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}