#include "Scene.h"
#include "Shotgun.h"
#include "NailGun.h"

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
	SHAPE shapeInfo; shapeInfo.type = box; shapeInfo.box = { 1000,0.1,1000 };
	suelo = new StaticRigidBody(shapeInfo, { 0,0,0 }, { 0.3,0.3,0.3,1 });
	statics.push_back(suelo);


	for (auto s : statics) {
		s->Init(gPhysics);
	}
	gScene->addActor(*suelo->_rigidStatic());
	sys = new RBSystem(gScene);
	
	//creamos las pistolas
	Shotgun* shotgun = new Shotgun(gPhysics, GetCamera(), &shotgunBool);
	sys->addParticleGenerator(shotgun);
	NailGun* nailgun = new NailGun(gPhysics, GetCamera(), &nailgunBool, 80, 3, 1);
	sys->addParticleGenerator(nailgun);
	//crea la pelota
	shapeInfo.type = sphere; shapeInfo.sphere = { 5 };
	DynamicRigidBody* ball = new DynamicRigidBody(shapeInfo, { 0,5,0 }, { 0.5,0.7,0.2,1 });
	ball->Init(gPhysics);
	dynamics.push_back(ball);
	gScene->addActor(*ball->_rigidDynamic());

	//crea la mirilla
	mirilla = new Particle(GetCamera()->getEye(), { 0,0,0 }, { 0,0,0 }, { 0,1,0,1 } , 0.99,-1.0f,0.0f,1000000.0F,
		CreateShape(((physx::PxSphereGeometry)(0.01))));
	
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
	delete sys;
}
void Scene::updateDefault(double t)
{
	sys->update(t);
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
