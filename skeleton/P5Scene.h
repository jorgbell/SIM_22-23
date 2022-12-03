#pragma once
#include "Scene.h"
#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"
#include "WhirlwindForceGenerator.h"
#include "ExplosionForceGenerator.h"
#include "ParticleSystem.h"
#include "UniformParticleGenerator.h"

class P5Scene : public Scene
{
public:
	P5Scene(PxPhysics* gPhys, PxScene* gSc, PxMaterial* gMat, Camera* cam, std::stack<Scene*> sceneManager);
	// Heredado vía Scene
	virtual void Init() override;
	virtual void Release() override;
	virtual void update(double t) override;
	virtual void keyPress(unsigned char key) override;
private:
	
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
};

