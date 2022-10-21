#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>
#include <queue>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Particle.h"
#include "Projectile_Pistol.h"
#include "ParticleSystem.h"
#include "GaussianParticleGenerator.h"

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
std::queue<Projectile_Pistol*> pistol; //cola de proyectiles. Uso una cola para eliminar el primero que entre cuando llegue al maximo de proyectiles en pantalla
int MAX_CURRENT_PROJECTILES = 20;
//datos del plano usado como referencia
RenderItem* ground;
Transform boxt = { 200, 100, 0 };
#pragma endregion

#pragma region Practica_2
ParticleSystem* sys;
GaussianParticleGenerator* gen;
GaussianParticleGenerator* gen2;
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
	ground = new RenderItem(CreateShape(physx::PxBoxGeometry(100.0, 0.5, 100.0)), &boxt, Vector4(0.5, 0.5, 0.5, 1));
	RegisterRenderItem(ground);
#pragma endregion

#pragma region Practica_2
	sys = new ParticleSystem();
	Vector3 deviationPos = Vector3(5, 0.01, 5);
	Vector3 deviationVel = Vector3(8, 8,8);
	Particle* base2 = new Particle();
	gen2 = new GaussianParticleGenerator("FuenteNormal", boxt.p, Vector3(5, 30, 5), 10, base2, deviationPos, deviationVel, 10, 0.6);
	Projectile_Pistol* base = new Projectile_Pistol(GetCamera()->getEye(), GetCamera()->getDir(), Vector4(0.5, 0.5, 0, 1));
	gen = new GaussianParticleGenerator("FuentePistol", GetCamera()->getEye(), base->getVel(), 10, base, deviationPos, deviationVel, 10, 0.6);
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
	/*
	//_p->integrate(t);
	//para integrar usando la estructura de datos de la cola, debemos realizar una copia de la cola original
	//para poder iterar sobre ella
	std::queue<Projectile_Pistol*> q_copy = pistol;
	while (!q_copy.empty()) {
		q_copy.front()->integrate(t); q_copy.pop();
	}
	*/
#pragma endregion
#pragma region Practica_2
	sys->update(t);
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
	/*
	while (!pistol.empty()) {
		auto p = pistol.front();
		pistol.pop();
		delete p;
	}
	*/
	//delete _p;
#pragma endregion
#pragma region Practica_2
	delete sys;
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
#pragma region Practica_1
		/*
			//si llega al maximo generados definidos previamente, elimina el primero creado.
			//hecho de manera previa al generador de particulas, lo ideal seria darles un tiempo de vida

		if (pistol.size() >= MAX_CURRENT_PROJECTILES) {
			auto p = pistol.front();
			pistol.pop();
			delete p;
		}
		pistol.push(new Projectile_Pistol(GetCamera()->getEye(), GetCamera()->getDir(), Vector4(0.5, 0.5, 0, 1)));
		*/
#pragma endregion
#pragma region Practica_2
		if (sys->getNumGenerators() > 0) {//si hay alguno en pantalla, no puede añadirlo. Si el que esta en pantalla es el mismo, se desactiva con este boton
			if (sys->getParticleGenerator("FuentePistol")) {
				sys->erase("FuentePistol");
			}
		}
		else {
			sys->add(gen);
		}
#pragma endregion
		break;
	case 'O':
#pragma region Practica_2
		if (sys->getNumGenerators() > 0) {//si hay alguno en pantalla, no puede añadirlo. Si el que esta en pantalla es el mismo, se desactiva con este boton
			if (sys->getParticleGenerator("FuenteNormal")) {
				sys->erase("FuenteNormal");
			}
		}
		else {
			sys->add(gen2);
		}
#pragma endregion
		break;

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