#pragma once
#include <ctype.h>
#include <stack>
#include <iostream>
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"
#include "WhirlwindForceGenerator.h"
#include "ExplosionForceGenerator.h"
#include "ParticleSystem.h"
#include "UniformParticleGenerator.h"

using namespace physx;

enum SCENES {
	DEFAULT, P5
};

class Scene
{
public:
	Scene(PxPhysics* gPhys, PxScene* gSc, PxMaterial* gMat, Camera* cam);
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
	SCENES actualScene = SCENES::DEFAULT;
	PxPhysics* gPhysics;
	PxScene* gScene;
	PxMaterial* gMaterial;
	Camera* camera;


	/*
			++++++++++++++++++++++++++++++++++DEFAULT SCENE++++++++++++++++++++++++++++++++++++++++++++++++
	*/
#pragma region DEFAULT
	GravityForceGenerator* earthGravity;
	GravityForceGenerator* moonGravity;
	GravityForceGenerator* smokeGravity;
	WindForceGenerator* wind;
	WhirlwindForceGenerator* whirlwind;
	ExplosionForceGenerator* explosion;
	bool exploded;
	//datos del plano usado como referencia
	RenderItem* ground;
	Transform boxt = { 200, 100, 0 };

	//ejercicio 1
	Particle* base;
	ParticleSystem* sys;
	UniformParticleGenerator* FuenteWind;
	UniformParticleGenerator* FuenteWhirlWind;
	UniformParticleGenerator* FuenteExplosion;
#pragma endregion
	/*
			++++++++++++++++++++++++++++++++++P5 SCENE++++++++++++++++++++++++++++++++++++++++++++++++
	*/
	
};

