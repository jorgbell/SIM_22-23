#include "Scene.h"
//RB
#include "Shotgun.h"
#include "NailGun.h"
#include "WindRBFG.h"
#include "WhirlwindRBFG.h"
//Particles
#include "WhirlwindForceGenerator.h"
#include "WhirlwindForceGenerator.h"
#include "UniformParticleGenerator.h"
#include "GravityForceGenerator.h"

Scene::Scene(PxPhysics* gPhys, PxScene* gSc, PxMaterial* gMat, Camera* cam, SCENES initScene) :
	gPhysics(gPhys), gScene(gSc), gMaterial(gMat), actualScene(initScene)
{
	Init();
}

Scene::~Scene()
{
	Release();
}

void Scene::Init()
{
	switch (actualScene)
	{
	case DEFAULT:
		initDefault();
		break;
	default:
		break;
	}

}

void Scene::Release()
{
	switch (actualScene)
	{
	case DEFAULT:
		releaseDefault();
		break;
	default:
		break;
	}

}

void Scene::update(double t)
{
	switch (actualScene)
	{
	case DEFAULT:
		updateDefault(t);
		break;
	default:
		break;
	}
}

void Scene::keyPress(unsigned char key)
{
	switch (toupper(key))
	{
	case '0':
		changeScene(SCENES::DEFAULT);
		return;
		break;
	default:
		break;
	};

	switch (actualScene)
	{
	case DEFAULT:
		keyDefault(key);
		break;
	default:
		break;
	}

}

void Scene::changeScene(SCENES newScene)
{
	if (actualScene == newScene)
		return;
	Release();
	actualScene = newScene;
	Init();
}


/*
++++++++++++++++++++++++++++++++++++++++++++DEFAULT SCENE++++++++++++++++++++++++++++++++++++++++++++++++
*/
#pragma region DEFAULT
void Scene::initDefault()
{
	/*+++++++++++++++++++++RIGIDBODY++++++++++++++++++++++++++++*/
	//RB ESTATICOS
	SHAPE shapeInfo; shapeInfo.type = box; shapeInfo.box = { 1000,0.1,1000 };
	suelo = new StaticRigidBody(shapeInfo, { 0,0,0 }, { 0.3,0.3,0.3,1 });
	statics.push_back(suelo);
	for (auto s : statics) {
		s->Init(gPhysics);
	}
	gScene->addActor(*suelo->_rigidStatic());
	RBsys = new RBSystem(gScene);
	//creamos las pistolas
	Shotgun* shotgun = new Shotgun(gPhysics, GetCamera(), &shotgunBool);
	RBsys->addParticleGenerator(shotgun);
	NailGun* nailgun = new NailGun(gPhysics, GetCamera(), &nailgunBool, 80, 3, 1);
	RBsys->addParticleGenerator(nailgun);
	//crea la pelota
	shapeInfo.type = sphere; shapeInfo.sphere = { 5 };
	DynamicRigidBody* ball = new DynamicRigidBody(shapeInfo, { 0,5,0 }, { 0.5,0.7,0.2,1 });
	ball->Init(gPhysics);
	gScene->addActor(*ball->_rigidDynamic());
	RBsys->addToParticlePool(ball);
	//crea los generadores de fuerzas
	WhirlwindRBFG* whirl = new WhirlwindRBFG(whirlPos, whirlRadius, { 1,0,0,0 }, 8, 0.3);
	RBsys->addToForceRegistry(whirl, ball);
	WindRBFG* wind = new WindRBFG({ 0,30,0 }, windPos, windRadius, { 0,1,0,0 }, 10, 2);
	RBsys->addToForceRegistry(wind, ball);
	


	/*PARTICLES*/
	//crea la mirilla
	mirilla = new Particle(GetCamera()->getEye(), { 0,0,0 }, { 0,0,0 }, { 0,1,0,1 }, 0.99, -1.0f, 0.0f, 1000000.0F,
		CreateShape(((physx::PxSphereGeometry)(0.01))));
	//crea el sistema de particulas
	PSys = new ParticleSystem();
	////creamos los generadores de partículas
	//Particle* baseParticle = new Particle();
	//UniformParticleGenerator* FuenteWind = new UniformParticleGenerator("FuenteWind", {windPos.x, 0, windPos.z}, Vector3(0, 10, 0), {0,1,0,1}, 1, baseParticle, {30,0.1,30}, {3,0.1,3}, 0.6, 3);
	//UniformParticleGenerator* FuenteWhirlWind = new UniformParticleGenerator("FuenteWhirlWind", whirlPos, Vector3(0, 2, 0), { 1,0,0,1 }, 1, baseParticle, { 50,10,50 }, { 3,3,3 }, 2, 4);
	////creamos los generadores de fuerzas
	//GravityForceGenerator* smokeGravity = new GravityForceGenerator({ 0,-0.50,0 });
	//GravityForceGenerator* earthGravity = new GravityForceGenerator({ 0,-9.8,0 });
	//WhirlwindForceGenerator* particleWhirl = new WhirlwindForceGenerator(whirlPos, whirlRadius, { 1,0,0,0 }, 0.6);
	//WindForceGenerator* particleWind = new WindForceGenerator({ 0,10,0 }, windPos, windRadius, { 0,1,0,0 }, 1, 0.01);
	////añadimos todo al sistema
	//FuenteWind->addForceGenerator(smokeGravity); FuenteWhirlWind->addForceGenerator(earthGravity);
	//FuenteWhirlWind->addForceGenerator(particleWhirl); FuenteWind->addForceGenerator(particleWind);
	//PSys->addParticleGenerator(FuenteWind); PSys->addParticleGenerator(FuenteWhirlWind);


}
void Scene::releaseDefault()
{
	while (!statics.empty()) {
		auto o = statics.back();
		auto rs = o->_rigidStatic();
		gScene->removeActor(*rs);
		delete o;
		statics.pop_back();
	}
	while (!dynamics.empty()) {
		auto o = dynamics.back();
		auto rd = o->_rigidDynamic();
		gScene->removeActor(*rd);
		delete o;
		dynamics.pop_back();
	}
	delete RBsys;
}
void Scene::updateDefault(double t)
{
	RBsys->update(t);
	PSys->update(t);
	Vector3 pos = GetCamera()->getEye() + GetCamera()->getDir().getNormalized() * 2;

	mirilla->setPos(pos);
}
void Scene::keyDefault(unsigned char key)
{
	switch (toupper(key))
	{
	case 'C':
		shotgunBool = true;
		break;
	case 'X':
		nailgunBool = true;
		break;
	default:
		break;
	}
}
#pragma endregion
