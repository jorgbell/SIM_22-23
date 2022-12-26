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
using namespace physx;

enum SCENES {
	DEFAULT
};

class Scene
{
public:
	Scene(PxPhysics* gPhys, PxScene* gSc, PxMaterial* gMat, Camera* cam, SCENES initScene = SCENES::DEFAULT);
	~Scene();
	// Heredado vía Scene
	void Init();
	void Release();
	void update(double t);
	void keyPress(unsigned char key);
	void changeScene(SCENES newScene);
	//*************METHODS PER SCENE*******************
#pragma region DEFAULT
	void initDefault();
	void releaseDefault();
	void updateDefault(double t);
	void keyDefault(unsigned char key);
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
	StaticRigidBody* suelo;	//plano usado como referencia
	bool shotgunBool = false; //para gestionar los disparos
	bool nailgunBool = false; //para gestionar los disparos
	Particle* mirilla;
	//Posiciones para los generadores
	Vector3 whirlPos = { 10,0,10 };	int whirlRadius = 100;
	Vector3 windPos = { 30,45,30 }; int windRadius = 40;
#pragma endregion


};

