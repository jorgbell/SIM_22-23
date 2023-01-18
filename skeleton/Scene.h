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
#include "FireworksSystem.h"
#include "BuoyancyFG.h"
#include "Player.h"
using namespace physx;

enum SCENES {
	DEFAULT, LEVEL1, LEVEL2, LEVEL3
};

class Scene
{
public:
	Scene(PxPhysics* gPhys, PxScene* gSc, PxMaterial* gMat, Camera* cam, std::string *text,SCENES initScene = SCENES::DEFAULT);
	~Scene();
	// Heredado vía Scene
	void Init();
	void Release();
	void update(double t);
	void keyPress(std::map<char,bool> keyboard, std::map<int, bool> mouse);
	void changeScene(SCENES newScene);
	void onCollision(physx::PxActor* actor1, physx::PxActor* actor2);
	SCENES getState() { return actualScene; }
	//*************METHODS PER SCENE*******************
#pragma region DEFAULT
	void initDefault();
	void releaseDefault();
	void updateDefault(double t);
	void keyDefault(std::map<char, bool> keyboard, std::map<int, bool> mouse);
	bool blasted(Transform t, Vector3 obj, int r);
	void onCollisionDefault(physx::PxActor* actor1, physx::PxActor* actor2);
	
#pragma endregion
#pragma region LEVEL1
	void initLevel1();
	void releaseLevel1();
	void updateLevel1(double t);
	void keyLevel1(std::map<char, bool> keyboard, std::map<int, bool> mouse);
	void onCollisionLevel1(physx::PxActor* actor1, physx::PxActor* actor2);
#pragma endregion
#pragma region LEVEL2
	void initLevel2();
	void releaseLevel2();
	void updateLevel2(double t);
	void keyLevel2(std::map<char, bool> keyboard, std::map<int, bool> mouse);
	void onCollisionLevel2(physx::PxActor* actor1, physx::PxActor* actor2);
#pragma endregion
#pragma region LEVEL3
	void initLevel3();
	void releaseLevel3();
	void updateLevel3(double t);
	void keyLevel3(std::map<char, bool> keyboard, std::map<int, bool> mouse);
	void onCollisionLevel3(physx::PxActor* actor1, physx::PxActor* actor2);
#pragma endregion


private:
	SCENES actualScene;
	PxPhysics* gPhysics;
	PxScene* gScene;
	PxMaterial* gMaterial;
	Camera* camera;
	std::string* display;

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
	bool nailgunBool = false; 
	bool jetpackBool = false; 
	bool shootFirework = false;
	bool win = false;
	Particle* mirilla = nullptr;
	Transform blastZone; int blastRadius; Particle* blast;
	Particle* baseParticle;
	GravityForceGenerator* smokeGravity; GravityForceGenerator* earthGravity;
	FireworksSystem* fireworks;

	BuoyancyFG* buoyancy = nullptr;
	Particle* backToDefault = nullptr; void createBackZone(); Vector3 backZonePos = { -360,10,-360 };

	Player* playerobj;
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
	std::vector<StaticRigidBody*> level3Rocks;
	UniformParticleGenerator* fuenteWindL3_0; UniformParticleGenerator* fuenteWindL3_1;
	UniformParticleGenerator* fuenteWindL3_2; 
	WindForceGenerator* particleWindL3_0; WindForceGenerator* particleWindL3_1;
	WindForceGenerator* particleWindL3_2;
	WindRBFG* rbWindL3_0; WindRBFG* rbWindL3_1; WindRBFG* rbWindL3_2;

	WhirlwindRBFG* rbWhirlL3_0; WhirlwindForceGenerator* particleWhirlL3_0; UniformParticleGenerator* fuenteWhirlL3_0;
	WhirlwindRBFG* rbWhirlL3_1; WhirlwindForceGenerator* particleWhirlL3_1; UniformParticleGenerator* fuenteWhirlL3_1;
#pragma endregion


};

