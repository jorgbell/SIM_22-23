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
using namespace physx;

enum SCENES {
	DEFAULT, P5
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
#pragma region P5
	void initP5();
	void releaseP5();
	void updateP5(double t);
	void keyP5(unsigned char key);
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
	//datos del plano usado como referencia
	RenderItem* ground;
	Transform boxt = { 0, 0, 0 };
#pragma endregion
	/*
			++++++++++++++++++++++++++++++++++P5 SCENE++++++++++++++++++++++++++++++++++++++++++++++++
	*/
#pragma region P5
	std::list<DynamicRigidBody*> dynamics;
	std::list<StaticRigidBody*> statics;

	StaticRigidBody* suelo;
	StaticRigidBody* pared;
	RBSystem* sys;
	bool shoot = false;
	bool exploded = false;


#pragma endregion

};

