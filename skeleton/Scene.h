#pragma once
#include <ctype.h>
#include <stack>
#include <iostream>
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include <list>
#include "Static_Dynamic_Body.h"
#include "RBSystem.h"
#include "RBShootGenerator.h"
#include "ExplosionRBFG.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "UniformParticleGenerator.h"
#include "WindForceGenerator.h"
#include "WhirlwindForceGenerator.h"
#include "WindRBFG.h"
#include "WhirlWindRBFG.h"
#include "GravityForceGenerator.h"
using namespace physx;

enum SCENES {
	DEFAULT, LEVEL1, LEVEL2, LEVEL3
};

class Scene
{
public:
	Scene(PxPhysics* gPhys, PxScene* gSc, PxMaterial* gMat, Camera* cam, SCENES initScene = SCENES::DEFAULT);
	~Scene();
	// Heredado v�a Scene
	void Init();
	void Release();
	void update(double t);
	void keyPress(unsigned char key);
	void changeScene(SCENES newScene);
	void onCollision(physx::PxActor* actor1, physx::PxActor* actor2);
	SCENES getState() { return actualScene; }
	//*************METHODS PER SCENE*******************
#pragma region DEFAULT
	void initDefault();
	void releaseDefault();
	void updateDefault(double t);
	void keyDefault(unsigned char key);
	bool blasted(Transform t, Vector3 obj, int r);
	void onCollisionDefault(physx::PxActor* actor1, physx::PxActor* actor2);
#pragma endregion

#pragma region LEVEL1
	void initLevel1();
	void releaseLevel1();
	void updateLevel1(double t);
	void keyLevel1(unsigned char key);
	void onCollisionLevel1(physx::PxActor* actor1, physx::PxActor* actor2);
#pragma endregion


#pragma region LEVEL2
	void initLevel2();
	void releaseLevel2();
	void updateLevel2(double t);
	void keyLevel2(unsigned char key);
	void onCollisionLevel2(physx::PxActor* actor1, physx::PxActor* actor2);
#pragma endregion


#pragma region LEVEL3
	void initLevel3();
	void releaseLevel3();
	void updateLevel3(double t);
	void keyLevel3(unsigned char key);
	void onCollisionLevel3(physx::PxActor* actor1, physx::PxActor* actor2);
#pragma endregion


private:
	SCENES actualScene;
	PxPhysics* gPhysics;
	PxScene* gScene;
	PxMaterial* gMaterial;
	Camera* camera;

	/*
			++++++++++++++++++++++++++++++++++DEFAULT SCENE++++++++++++++++++++++++++++++++++++++++++++++++
	*/
#pragma region DEFAULT
	RBSystem* RBsys;
	ParticleSystem* PSys;
	std::list<DynamicRigidBody*> dynamics;
	std::list<StaticRigidBody*> statics;
	DynamicRigidBody* ball; //pelota de juego
	bool shotgunBool = false; //para gestionar los disparos
	bool nailgunBool = false; //para gestionar los disparos
	bool win = false;
	Particle* mirilla;
	Transform blastZone; int blastRadius; RenderItem* blast;
	Particle* baseParticle;
	GravityForceGenerator* smokeGravity; GravityForceGenerator* earthGravity;
#pragma endregion
	/*
		++++++++++++++++++++++++++++++++++LEVEL 1++++++++++++++++++++++++++++++++++++++++++++++++
*/
#pragma region LEVEL1
//Posiciones para los generadores
	UniformParticleGenerator* fuenteWindL1; UniformParticleGenerator* fuenteWhirlL1;
	WhirlwindForceGenerator* particleWhirlL1; WindForceGenerator* particleWindL1;
	WhirlwindRBFG* rbWhirlL1; WindRBFG* rbWindL1;

#pragma endregion
/*
	++++++++++++++++++++++++++++++++++LEVEL 2++++++++++++++++++++++++++++++++++++++++++++++++
*/
#pragma region LEVEL2
	UniformParticleGenerator* fuenteWindL2_0; UniformParticleGenerator* fuenteWindL2_1;
	UniformParticleGenerator* fuenteWindL2_2; UniformParticleGenerator* fuenteWindL2_3;
	WindForceGenerator* particleWindL2_0; WindForceGenerator* particleWindL2_1;
	WindForceGenerator* particleWindL2_2; WindForceGenerator* particleWindL2_3;
	WindRBFG* rbWindL2_0; WindRBFG* rbWindL2_1; WindRBFG* rbWindL2_2; WindRBFG* rbWindL2_3;
	WhirlwindRBFG* rbWhirlL2; WhirlwindForceGenerator* particleWhirlL2; UniformParticleGenerator* fuenteWhirlL2;
#pragma endregion
/*
++++++++++++++++++++++++++++++++++LEVEL 3++++++++++++++++++++++++++++++++++++++++++++++++
*/
#pragma region LEVEL3

#pragma endregion


};

