#include "Scene.h"

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
	case P5:
		initP5();
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
	case P5:
		releaseP5();
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
	case P5:
		updateP5(t);
		break;
	default:
		break;
	}
}

void Scene::keyPress(unsigned char key)
{
	switch (toupper(key))
	{
	case '5':
		changeScene(SCENES::P5);
		return;
		break;
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
	case P5:
		keyP5(key);
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
	ground = new RenderItem(CreateShape(
			physx::PxBoxGeometry(1000.0, 0.5, 1000.0)), &boxt, Vector4(0.5, 0.5, 0.5, 1));
	
}
void Scene::releaseDefault()
{
	ground->release();
}
void Scene::updateDefault(double t)
{
	;
}
void Scene::keyDefault(unsigned char key)
{
	switch (toupper(key))
	{
	default:
		break;
	}
}
#pragma endregion

/*
		++++++++++++++++++++++++++++++++++P5 SCENE++++++++++++++++++++++++++++++++++++++++++++++++
*/

#pragma region P5
void Scene::initP5()
{
	//+++++++++++++++++++++++CREATE STATIC BODIES++++++++++++++++++++++++++++++++
	SHAPE shapeInfo; shapeInfo.type = box; shapeInfo.box = { 1000,0.1,1000 };
	suelo = new StaticRigidBody(shapeInfo, { 0,0,0 }, { 0.1,0.3,0.8,1 });
	shapeInfo.box = { 40,20,5 };
	pared = new StaticRigidBody(shapeInfo, { 10,20,-30 }, { 0.8,0.3,0.1,1 });

	statics.push_back(suelo);
	statics.push_back(pared);
	for (auto s : statics) {
		s->Init(gPhysics);
	}
	gScene->addActor(*suelo->_rigidStatic());
	gScene->addActor(*pared->_rigidStatic());


	//Sistema de rb
	sys = new RBSystem(gScene);
	RBShootGenerator* gen = new RBShootGenerator("ShootGenerator", gPhysics, GetCamera(), { 3,-2,-5 }, &shoot, { 0,0,0 }, { 0,0,20 }, { 0,0,0 }, { 0.5, 1, 0.5, 1 });
	ExplosionRBFG* explosion = new ExplosionRBFG({ 10, -0, 10 }, { 1,0,0,0 }, 1000, 20, 2, &exploded);
	gen->addForceGenerator(explosion);
	sys->addParticleGenerator(gen);

}
void Scene::releaseP5()
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
void Scene::updateP5(double t)
{
	sys->update(t);
	shoot = false; exploded = false;
}
void Scene::keyP5(unsigned char key)
{
	switch (toupper(key))
	{
	case 'V':
		shoot = true;
		break;
	case 'E':
		exploded = true;
		break;
	default:
		break;
	}
}
#pragma endregion
