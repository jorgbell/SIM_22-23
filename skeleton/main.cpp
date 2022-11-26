#include <ctype.h>
#include <PxPhysicsAPI.h>
#include <vector>
#include <queue>
//#include "checkML.h"
#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Particle.h"
#include "Projectile_Pistol.h"
#include "ParticleSystem.h"
#include "GaussianParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "FireworksSystem.h"
#include "Firework.h"
#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"
#include "WhirlwindForceGenerator.h"
#include "ExplosionForceGenerator.h"
#include "AnchoredSpringFG.h"
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
//ejercicio 1
Particle* base;
ParticleSystem* sys;
UniformParticleGenerator* FuenteWind;
UniformParticleGenerator* FuenteWhirlWind;
UniformParticleGenerator* FuenteExplosion;
//ejercicio 2
FireworksSystem* fSys;
#pragma endregion

#pragma region Practica_3
GravityForceGenerator* earthGravity;
GravityForceGenerator* moonGravity;
GravityForceGenerator* smokeGravity;
WindForceGenerator* wind;
WhirlwindForceGenerator* whirlwind;
ExplosionForceGenerator* explosion;
bool exploded;
#pragma endregion

#pragma region Practica_4
AnchoredSpringFG* anchor;
bool created = false;
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
	//EJERCICIO 1
	sys = new ParticleSystem();

	//base = new Particle();
	//FuenteWind = new UniformParticleGenerator("FuenteWind", boxt.p, Vector3(0, 10, 0), { 0,1,0,1 }, 3, base, { 30,0.1,30 }, {3,0.1,3},0.6, 30);
	//FuenteWhirlWind = new UniformParticleGenerator("FuenteWhirlWind", boxt.p, Vector3(0, 2, 0), { 1,0,0,1 }, 3, base, { 50,10,50 }, { 3,3,3 }, 2,10);
	//FuenteExplosion = new UniformParticleGenerator("FuenteExplosion", boxt.p, Vector3(0, 20, 0), { 0,0,1,1 }, 1, base, { 30,0.1,30 }, { 3,0.1,3 }, 0.6,10);

	////EJERCICIO 2
	//fSys = new FireworksSystem();
#pragma endregion

#pragma region Practica_3
	earthGravity = new GravityForceGenerator(Vector3(0, -9.8, 0));
	moonGravity = new GravityForceGenerator(Vector3(0, -1.62, 0));
	smokeGravity = new GravityForceGenerator(Vector3(0, -0.50, 0));
	Vector3 windRegion = { boxt.p.x, boxt.p.y + 45, boxt.p.z };
	Vector3 whirlwindRegion = { boxt.p.x+20, boxt.p.y, boxt.p.z-10 };

	wind = new WindForceGenerator({ 2,2,10 }, windRegion, 40, { 0,1,0,0 }, 1,0.01);
	/*whirlwind = new WhirlwindForceGenerator(whirlwindRegion, 100, {1,0,0,0}, 0.6);
	FuenteWind->addForceGenerator(smokeGravity);
	FuenteWind->addForceGenerator(wind);

	explosion = new ExplosionForceGenerator(windRegion, { 0,0,1,0 }, 100, 50, 2, &exploded);


	FuenteWhirlWind->addForceGenerator(earthGravity);
	FuenteWhirlWind->addForceGenerator(whirlwind);

	FuenteExplosion->addForceGenerator(explosion);
	FuenteExplosion->addForceGenerator(moonGravity);*/
	exploded = false;
#pragma endregion

#pragma region Practica_4
	//una particula unida a un objeto estatico
	anchor = new AnchoredSpringFG(1,10,{boxt.p.x, boxt.p.y+40, boxt.p.z});
	Particle* p = new Particle({ boxt.p.x+5, boxt.p.y + 40, boxt.p.z });
	sys->addToParticlePool(p);
	sys->addToForceRegistry(anchor, p);
	sys->addToForceRegistry(earthGravity, p);
	//dos particulas unidas la una a la otra
	



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
	//fSys->update(t);
#pragma endregion

	gScene->simulate(t);
	gScene->fetchResults(true);
	if (exploded)
		exploded = false;
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
	/*delete FuenteWind;
	delete FuenteWhirlWind;
	delete fSys;*/
	delete base;
	delete ground;
	delete earthGravity;
	delete moonGravity;
	/*delete wind;
	delete whirlwind;
	delete explosion;*/
	delete anchor;
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
#pragma region Practica2
		//if (sys->getNumGenerators() > 0) {//si hay alguno en pantalla, no puede añadirlo. Si el que esta en pantalla es el mismo, se desactiva con este boton
		//	if (sys->getParticleGenerator("FuenteWind")) {
		//		sys->erase("FuenteWind");
		//	}
		//}
		//else {
		//	sys->addParticleGenerator(FuenteWind);
		//}
#pragma endregion
#pragma region Practica_4
		if (!created) {
			//dos particulas unidas por un muelle. A una le afecta la gravedad de la Tierra, a otra la de la Luna, y a ambas la fuerza del viento por igual.
			Particle* p1 = new Particle({ boxt.p.x-10, boxt.p.y + 60, boxt.p.z });
			Particle* p2 = new Particle({ boxt.p.x-10, boxt.p.y + 45, boxt.p.z + 10 });
			p1->setColor({ 1,0,1,1 }); p1->setDamp(0.85);
			p2->setColor({ 1,1,0,1 }); p1->setDamp(0.85); p2->setMass(10.0);
			SpringForceGenerator* f1 = new SpringForceGenerator(1, 10, p2);
			SpringForceGenerator* f2 = new SpringForceGenerator(1, 10, p1);			
			sys->addToParticlePool(p1);	sys->addToParticlePool(p2);
			sys->addToForceRegistry(f1, p1);	sys->addToForceRegistry(f2, p2);
			sys->addToForceRegistry(wind, p1);	sys->addToForceRegistry(wind, p2);
			sys->addToForceRegistry(earthGravity, p1);	sys->addToForceRegistry(moonGravity, p2);
			created = true;
		}
		
#pragma endregion

		break;
	case 'O':
#pragma region Practica_2
		//if (sys->getNumGenerators() > 0) {//si hay alguno en pantalla, no puede añadirlo. Si el que esta en pantalla es el mismo, se desactiva con este boton
		//	if (sys->getParticleGenerator("FuenteWhirlWind")) {
		//		sys->erase("FuenteWhirlWind");
		//	}
		//}
		//else {
		//	sys->addParticleGenerator(FuenteWhirlWind);
		//}
#pragma endregion
		break;
	case 'F':
#pragma region Practica_2
		//fSys->startFire(boxt.p, Vector3(0, 20, 0), FIREWORK_5);
#pragma endregion
		break;
	case 'I':
#pragma region Practica_3
		//if (sys->getNumGenerators() > 0) {//si hay alguno en pantalla, no puede añadirlo. Si el que esta en pantalla es el mismo, se desactiva con este boton
		//	if (sys->getParticleGenerator("FuenteExplosion")) {
		//		sys->erase("FuenteExplosion");
		//	}
		//}
		//else {
		//	sys->addParticleGenerator(FuenteExplosion);
		//}
		//break;
#pragma endregion
	case 'E':
		//exploded = !exploded;
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