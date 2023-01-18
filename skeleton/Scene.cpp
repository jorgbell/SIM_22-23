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
#include "JetpackForceGenerator.h"
#include "BuoyancyFG.h"
#include <iostream>

Scene::Scene(PxPhysics* gPhys, PxScene* gSc, PxMaterial* gMat, Camera* cam, std::string* text, SCENES initScene) :
	gPhysics(gPhys), gScene(gSc), gMaterial(gMat), actualScene(initScene), display(text)
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
	case LEVEL1:
		initLevel1();
		break;
	case LEVEL2:
		initLevel2();
		break;
	case LEVEL3:
		initLevel3();
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
	case LEVEL1:
		releaseLevel1();
		break;
	case LEVEL2:
		releaseLevel2();
		break;
	case LEVEL3:
		releaseLevel3();
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
	case LEVEL1:
		updateLevel1(t);
		break;
	case LEVEL2:
		updateLevel2(t);
		break;
	case LEVEL3:
		updateLevel3(t);
		break;
	default:
		break;
	}
}
void Scene::keyPress(std::map<char, bool> keyboard, std::map<int, bool> mouse)
{
	if(keyboard['0']) changeScene(SCENES::DEFAULT);
	if(keyboard['1']) changeScene(SCENES::LEVEL1);
	if(keyboard['2']) changeScene(SCENES::LEVEL2);
	if(keyboard['3']) changeScene(SCENES::LEVEL3);

	switch (actualScene)
	{
	case DEFAULT:
		keyDefault(keyboard, mouse);
		break;
	case LEVEL1:
		keyLevel1(keyboard, mouse);
		break;
	case LEVEL2:
		keyLevel2(keyboard, mouse);
		break;
	case LEVEL3:
		keyLevel3(keyboard, mouse);
		break;
	default:
		break;
	}

}
void Scene::onCollision(physx::PxActor* actor1, physx::PxActor* actor2) {
	switch (actualScene) {
	case DEFAULT:
		onCollisionDefault(actor1, actor2);
		break;
	case LEVEL1:
		onCollisionLevel1(actor1, actor2);
		break;
	case LEVEL2:
		onCollisionLevel2(actor1, actor2);
		break;
	case LEVEL3:
		onCollisionLevel3(actor1, actor2);
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
	win = false;
	RBsys = new RBSystem(gScene); 	PSys = new ParticleSystem();
	baseParticle = new Particle();
	//creamos los generadores de fuerzas
	smokeGravity = new GravityForceGenerator({ 0,-0.50,0 });
	earthGravity = new GravityForceGenerator({ 0,-9.8,0 });
	fireworks = new FireworksSystem();
	fireworks->setExploded(false);
	/*+++++++++++++++++++++RIGIDBODY++++++++++++++++++++++++++++*/
	//RB ESTATICOS
	SHAPE shapeInfo; shapeInfo.type = box; shapeInfo.box = { 400,7,400 };
	StaticRigidBody* suelo = new StaticRigidBody("static", shapeInfo, { 0,0,0 }, { 0.8,0.58,0.9,1 });
	shapeInfo.box = { 7,200,400 };
	StaticRigidBody* pared1 = new StaticRigidBody("static", shapeInfo, { 400,200,0 }, { 0.5,0.3,0.3,1 });
	StaticRigidBody* pared2 = new StaticRigidBody("static", shapeInfo, { -400,200,0 }, { 0.5,0.3,0.3,1 });
	shapeInfo.box = { 400,200,7 };
	StaticRigidBody* pared3 = new StaticRigidBody("static", shapeInfo, { 0,200,400 }, { 0.5,0.3,0.3,1 });
	StaticRigidBody* pared4 = new StaticRigidBody("static", shapeInfo, { 0,200,-400 }, { 0.5,0.3,0.3,1 });
	statics.push_back(suelo); statics.push_back(pared1); statics.push_back(pared2); statics.push_back(pared3); statics.push_back(pared4);
	for (auto s : statics) {
		s->Init(gPhysics);
		gScene->addActor(*s->_rigidStatic());
	}
	//creamos al jugador
	shapeInfo.box = { 8,8,8 };
	Particle* player = new Particle({ 100,100,100 }, { 0,0,0 }, { 0,0,0 }, { 1,1,0,1 }, 0.84, -1.0F, -100.0F, 1,
		CreateShape(physx::PxCapsuleGeometry(3, 3)));
	player->DeregisterParticle();
	PSys->addToParticlePool(player);
	JetpackForceGenerator* jetpack = new JetpackForceGenerator(50, 100, 0.2, &jetpackBool, display);
	PSys->addToForceRegistry(jetpack, player);
	PSys->addToForceRegistry(earthGravity, player);
	playerobj = new Player(GetCamera(), player, &jetpackBool);

	//creamos las pistolas
	Shotgun* shotgun = new Shotgun(gPhysics, GetCamera(), &shotgunBool);
	RBsys->addParticleGenerator(shotgun);
	NailGun* nailgun = new NailGun(gPhysics, GetCamera(), &nailgunBool, 80, 3, 1);
	RBsys->addParticleGenerator(nailgun);
	/*PARTICLES*/
	//crea la mirilla
	if (mirilla == nullptr) mirilla = new Particle(GetCamera()->getEye(), { 0,0,0 }, { 0,0,0 }, { 0,1,0,1 }, 0.99, -1.0f, 0.0f, 1000000.0F,
		CreateShape(((physx::PxSphereGeometry)(0.01))));

	//creamos las zonas para elegir nivel
	Vector4 colors[3] = { {0.8, 0.2, 0.3, 1}, {0.2,0.8,0.3,1}, {0.2,0.3,0.8,1} };
	for (int i = 3; i > 0; i--) {
		shapeInfo.type = box; shapeInfo.box = { 20,40,20 };
		Vector3 pos = { 200 - ((float)i * 100), 2, 0 };
		StaticRigidBody* levelTrigger;
		if (i == 3)
			levelTrigger = new StaticRigidBody("level_1", shapeInfo, pos, colors[i - 1]);
		else if (i == 2)
			levelTrigger = new StaticRigidBody("level_2", shapeInfo, pos, colors[i - 1]);
		else
			levelTrigger = new StaticRigidBody("level_3", shapeInfo, pos, colors[i - 1]);

		levelTrigger->Init(gPhysics);
		gScene->addActor(*levelTrigger->_rigidStatic());
		statics.push_back(levelTrigger);
	}


}
void Scene::releaseDefault()
{
	if (actualScene == DEFAULT) {
		//elimina los seleccionadores de niveles
		for (int i = 0; i < 3; i++) {
			auto o = statics.back();
			statics.pop_back();
			o->setPos({ -800,-800,-800 });
			o->actualiza();
			auto rd = o->_rigidStatic();
			gScene->removeActor(*rd);
			delete o;
		}
	}
	else {
		RBsys->clean(); PSys->clean();
		delete buoyancy;
		delete blast;
	}
}
void Scene::updateDefault(double t)
{
	RBsys->update(t);
	PSys->update(t);
	fireworks->update(t);
	playerobj->update(t);
	Vector3 pos = GetCamera()->getEye() + GetCamera()->getDir().getNormalized() * 2;
	mirilla->setPos(pos);
	if (actualScene != DEFAULT) {
		//comprobaciones
		if (blasted(blastZone, ball->getPos(), blastRadius) && !win) {
			win = true;
			fireworks->startFire(blastZone.p, { 0,50,0 }, FIREWORK_5);
			PSys->clear();
		}
		if (fireworks->isFinished())
			changeScene(DEFAULT);
		if (blasted(GetCamera()->getTransform(), backZonePos, 20))
			changeScene(DEFAULT);
	}
}
void Scene::keyDefault(std::map<char, bool> keyboard, std::map<int, bool> mouse)
{
	if(mouse[0]) shotgunBool = true;
	if(mouse[2]) nailgunBool = true;
	if (keyboard[' ']) {
		playerobj->stop();
		jetpackBool = true;
	}
}
void Scene::onCollisionDefault(physx::PxActor* actor1, physx::PxActor* actor2) {
	const char* n1 = actor1->getName(); const char* n2 = actor2->getName();
	if (n1 == "level_1" || n2 == "level_1") {
		changeScene(LEVEL1);
		return;
	}
	else if (n1 == "level_2" || n2 == "level_2") {
		changeScene(LEVEL2);
		return;
	}
	else if (n1 == "level_3" || n2 == "level_3") {
		changeScene(LEVEL3);
		return;
	}

}
bool Scene::blasted(Transform t, Vector3 obj, int r) {
	return (t.p - obj).magnitude() < r;
}
void Scene::createBackZone() {
	//crea la zona para volver al menu default
	backToDefault = blast = new Particle(backZonePos, { 0,0,0 }, { 0,0,0 }, { 0,1,1,1 }, 0.8, -1.0f, 0.0f, 5.0F,
		CreateShape(physx::PxCapsuleGeometry(5,4)));
	//una particula flotando
	PSys->addToParticlePool(backToDefault);
	buoyancy = new BuoyancyFG(1, 1000, { backZonePos.x,backZonePos.y - 3,backZonePos.z });
	PSys->addToForceRegistry(buoyancy, backToDefault);
	PSys->addToForceRegistry(smokeGravity, backToDefault);
}
#pragma endregion

/*
++++++++++++++++++++++++++++++++++++++++++++LEVEL 1++++++++++++++++++++++++++++++++++++++++++++++++
*/

#pragma region LEVEL1
void Scene::initLevel1() {
	createBackZone();
	win = false;
	fireworks->setExploded(false);
	blastZone = { 200, 10, 250 }; blastRadius = 30;
	blast = new Particle(blastZone.p, { 0,0,0 }, { 0,0,0 }, { 1,1,1,1 }, 0.8, -1.0f, 0.0f, 5.0F,
		CreateShape(physx::PxBoxGeometry(blastRadius, blastRadius, blastRadius)));
	//crea la pelota
	SHAPE shapeInfo;  shapeInfo.type = sphere; shapeInfo.sphere = { 5 };
	ball = new DynamicRigidBody("ball", shapeInfo, { -300,30,-200 }, { 0.5,0.6,0.2,1 });
	ball->Init(gPhysics);
	gScene->addActor(*ball->_rigidDynamic());
	RBsys->addToParticlePool(ball);

	//crea los generadores de fuerzas
	Vector3 whirlPos = { 0,30,0 }; double whirlRadius = 200;
	Vector3 windPos = { 130,30,100 }; double windRadius = 50;

	rbWhirlL1 = new WhirlwindRBFG(false, whirlPos, whirlRadius, { 1,0,0,0 }, 5, 0.3);
	RBsys->addToForceRegistry(rbWhirlL1, ball);
	rbWindL1 = new WindRBFG(false, { 0,30,0 }, windPos, windRadius, { 0,1,0,0 }, 15, 2);
	RBsys->addToForceRegistry(rbWindL1, ball);


	//creamos los generadores de partículas
	fuenteWindL1 = new UniformParticleGenerator("FuenteWind", { windPos.x, 0, windPos.z }, Vector3(0, 10, 0), { 0,1,0,1 }, 1, baseParticle, { 50,0.1,50 }, { 3,0.1,3 }, 0.6, 5);
	fuenteWhirlL1 = new UniformParticleGenerator("FuenteWhirlWind", { whirlPos.x, whirlPos.y - 20, whirlPos.z }, Vector3(0, 2, 0), { 1,0,0,1 }, 1, baseParticle, { 100,0.1,100 }, { 3,8,3 }, 2, 4);

	particleWhirlL1 = new WhirlwindForceGenerator(false, whirlPos, whirlRadius, { 1,0,0,0 }, 0.6);
	particleWindL1 = new WindForceGenerator(false, { 0,10,0 }, windPos, windRadius, { 0,1,0,0 }, 1, 0.01);
	//añadimos todo al sistema
	fuenteWindL1->addForceGenerator(smokeGravity); fuenteWhirlL1->addForceGenerator(earthGravity);
	fuenteWhirlL1->addForceGenerator(particleWhirlL1); fuenteWindL1->addForceGenerator(particleWindL1);
	PSys->addParticleGenerator(fuenteWindL1); PSys->addParticleGenerator(fuenteWhirlL1);

}
void Scene::releaseLevel1() {
	releaseDefault();
	//eliminar los generadores de particulas
	delete rbWhirlL1; delete rbWindL1; delete particleWhirlL1; delete particleWindL1;
	delete fuenteWhirlL1; delete fuenteWindL1;
}
void Scene::updateLevel1(double t) {

	updateDefault(t);
}
void Scene::keyLevel1(std::map<char, bool> keyboard, std::map<int, bool> mouse) {
	keyDefault(keyboard, mouse);
	//...
}

void Scene::onCollisionLevel1(physx::PxActor* actor1, physx::PxActor* actor2) {
	;
}
#pragma endregion

/*
++++++++++++++++++++++++++++++++++++++++++++LEVEL 2++++++++++++++++++++++++++++++++++++++++++++++++
*/

#pragma region LEVEL2
void Scene::initLevel2() {
	createBackZone();
	win = false;
	fireworks->setExploded(false);
	blastZone = { 0, 130, 0 }; blastRadius = 30;
	blast = new Particle(blastZone.p, { 0,0,0 }, { 0,0,0 }, { 1,1,1,1 }, 0.8, -1.0f, 0.0f, 5.0F,
		CreateShape(physx::PxBoxGeometry(blastRadius, blastRadius, blastRadius)));

	//crea la pelota
	SHAPE shapeInfo;  shapeInfo.type = sphere; shapeInfo.sphere = { 5 };
	ball = new DynamicRigidBody("ball", shapeInfo, { 0,30,0 }, { 0.5,0.6,0.2,1 });
	ball->Init(gPhysics);
	gScene->addActor(*ball->_rigidDynamic());
	RBsys->addToParticlePool(ball);

	//crea los generadores de fuerzas
	double whirlRadius = 200; double windRadius = 80;
	Vector3 whirlPos = { 0,330,0 };
	Vector3 windPos_0 = { -130,50,130 }; Vector3 windPos_1 = { 130,50,130 };
	Vector3 windPos_2 = { -130,50,-130 }; Vector3 windPos_3 = { 130,50,-130 };

	rbWhirlL2 = new WhirlwindRBFG(false, whirlPos, whirlRadius, { 1,0,0,0 }, 5, 0.3);
	RBsys->addToForceRegistry(rbWhirlL2, ball);
	rbWindL2_0 = new WindRBFG(false, { 0,50,0 }, windPos_0, windRadius, { 0,1,0,0 }, 15, 2);
	rbWindL2_1 = new WindRBFG(false, { 0,50,0 }, windPos_1, windRadius, { 0,1,0,0 }, 15, 2);
	rbWindL2_2 = new WindRBFG(false, { 0,50,0 }, windPos_2, windRadius, { 0,1,0,0 }, 15, 2);
	rbWindL2_3 = new WindRBFG(false, { 0,50,0 }, windPos_3, windRadius, { 0,1,0,0 }, 15, 2);
	RBsys->addToForceRegistry(rbWindL2_0, ball); RBsys->addToForceRegistry(rbWindL2_1, ball);
	RBsys->addToForceRegistry(rbWindL2_2, ball); RBsys->addToForceRegistry(rbWindL2_3, ball);


	//creamos los generadores de partículas
	fuenteWhirlL2 = new UniformParticleGenerator("FuenteWhirlWindL2", { whirlPos.x, whirlPos.y - 70, whirlPos.z }, Vector3(0, 2, 0), { 1,0,0,1 }, 1, baseParticle, { 100,0.1,100 }, { 3,8,3 }, 2, 4);
	particleWhirlL2 = new WhirlwindForceGenerator(false, whirlPos, whirlRadius, { 1,0,0,0 }, 0.6);
	fuenteWhirlL2->addForceGenerator(earthGravity); fuenteWhirlL2->addForceGenerator(particleWhirlL2);
	PSys->addParticleGenerator(fuenteWhirlL2);
	float wr = (float)windRadius - 30;
	fuenteWindL2_0 = new UniformParticleGenerator("FuenteWindL2_0", { windPos_0.x,0,windPos_0.z }, Vector3(0, 10, 0), { 0,1,0,1 }, 1, baseParticle, { wr,0.1,wr }, { 3,0.1,3 }, 0.6, 10);
	fuenteWindL2_1 = new UniformParticleGenerator("FuenteWindL2_1", { windPos_1.x,0,windPos_1.z }, Vector3(0, 10, 0), { 0,1,0,1 }, 1, baseParticle, { wr,0.1,wr }, { 3,0.1,3 }, 0.6, 10);
	fuenteWindL2_2 = new UniformParticleGenerator("FuenteWindL2_2", { windPos_2.x,0,windPos_2.z }, Vector3(0, 10, 0), { 0,1,0,1 }, 1, baseParticle, { wr,0.1,wr }, { 3,0.1,3 }, 0.6, 10);
	fuenteWindL2_3 = new UniformParticleGenerator("FuenteWindL2_3", { windPos_3.x,0,windPos_3.z }, Vector3(0, 10, 0), { 0,1,0,1 }, 1, baseParticle, { wr,0.1,wr }, { 3,0.1,3 }, 0.6, 10);
	particleWindL2_0 = new WindForceGenerator(false, { 0,10,0 }, windPos_0, windRadius, { 0,1,0,0 }, 1, 0.01);
	particleWindL2_1 = new WindForceGenerator(false, { 0,10,0 }, windPos_1, windRadius, { 0,1,0,0 }, 1, 0.01);
	particleWindL2_2 = new WindForceGenerator(false, { 0,10,0 }, windPos_2, windRadius, { 0,1,0,0 }, 1, 0.01);
	particleWindL2_3 = new WindForceGenerator(false, { 0,10,0 }, windPos_3, windRadius, { 0,1,0,0 }, 1, 0.01);
	//añadimos todo al sistema
	fuenteWindL2_0->addForceGenerator(smokeGravity);	fuenteWindL2_0->addForceGenerator(particleWindL2_0);
	fuenteWindL2_1->addForceGenerator(smokeGravity);	fuenteWindL2_1->addForceGenerator(particleWindL2_1);
	fuenteWindL2_2->addForceGenerator(smokeGravity);	fuenteWindL2_2->addForceGenerator(particleWindL2_2);
	fuenteWindL2_3->addForceGenerator(smokeGravity);	fuenteWindL2_3->addForceGenerator(particleWindL2_3);

	PSys->addParticleGenerator(fuenteWindL2_0); PSys->addParticleGenerator(fuenteWindL2_1);
	PSys->addParticleGenerator(fuenteWindL2_2); PSys->addParticleGenerator(fuenteWindL2_3);

}
void Scene::releaseLevel2() {
	releaseDefault();
	//eliminar los generadores de particulas
	delete rbWhirlL2; delete particleWhirlL2; delete fuenteWhirlL2;
	delete rbWindL2_0; delete rbWindL2_1; delete rbWindL2_2; delete rbWindL2_3;
	delete particleWindL2_0; delete particleWindL2_1; delete particleWindL2_2; delete particleWindL2_3;
	delete fuenteWindL2_0; delete fuenteWindL2_1; delete fuenteWindL2_2; delete fuenteWindL2_3;
}
void Scene::updateLevel2(double t) {
	updateDefault(t);
}
void Scene::keyLevel2(std::map<char, bool> keyboard, std::map<int, bool> mouse) {
	keyDefault(keyboard, mouse);
	//...
}
void Scene::onCollisionLevel2(physx::PxActor* actor1, physx::PxActor* actor2) {
	;
}
#pragma endregion

/*
++++++++++++++++++++++++++++++++++++++++++++LEVEL 3++++++++++++++++++++++++++++++++++++++++++++++++
*/

#pragma region LEVEL3
void Scene::initLevel3() {
	createBackZone();
	win = false;
	fireworks->setExploded(false);

	blastZone = { 0, 0, 350 }; blastRadius = 30;
	blast = new Particle(blastZone.p, { 0,0,0 }, { 0,0,0 }, { 1,1,1,1 }, 0.8, -1.0f, 0.0f, 5.0F,
		CreateShape(physx::PxBoxGeometry(blastRadius, blastRadius, blastRadius)));

	//crea la pelota
	SHAPE shapeInfo;  shapeInfo.type = sphere; shapeInfo.sphere = { 5 };
	ball = new DynamicRigidBody("ball", shapeInfo, { 0,40,-350 }, { 0.5,0.6,0.2,1 });
	ball->Init(gPhysics);
	gScene->addActor(*ball->_rigidDynamic());
	RBsys->addToParticlePool(ball);

	shapeInfo.type = box; shapeInfo.box = { 150,200,150 };
	StaticRigidBody* bigRock = new StaticRigidBody("bigRock", shapeInfo, { 0,100,0 }, { 0.8,0.5,1,1 });
	shapeInfo.box = { 90,100,40 };
	StaticRigidBody* bigRock2 = new StaticRigidBody("bigRockRight", shapeInfo, { 250,100,0 }, { 0.8, 0.5, 1, 1 });
	shapeInfo.box = { 10,100,90 };
	StaticRigidBody* bigRock3 = new StaticRigidBody("bigRock3", shapeInfo, { -100,100,280 });
	StaticRigidBody* bigRock4 = new StaticRigidBody("bigRock4", shapeInfo, { 100,100,280 });
	level3Rocks.push_back(bigRock); level3Rocks.push_back(bigRock2); level3Rocks.push_back(bigRock3); level3Rocks.push_back(bigRock4);
	for (auto o : level3Rocks) {
		o->Init(gPhysics);
		gScene->addActor(*o->_rigidStatic());
	}

	//a la izquierda, uno de viento normal
	//a la derecha, un tornado
	//enfrente, dos de viento normal

	//crea los generadores de fuerzas
	double whirlRadius = 150; double windRadius = 80;
	Vector3 whirlPos_0 = { 0,250,0 }; Vector3 whirlPos_1 = { -250,50,0 };

	Vector3 windPos_0 = { 250,50,-80 }; Vector3 windPos_1 = { -150,50,280 };
	Vector3 windPos_2 = { 150,50,280 };

	rbWhirlL3_0 = new WhirlwindRBFG(false, whirlPos_0, whirlRadius, { 1,0,0,0 }, 5, 0.3);
	RBsys->addToForceRegistry(rbWhirlL3_0, ball);
	rbWhirlL3_1 = new WhirlwindRBFG(false, whirlPos_1, whirlRadius, { 1,0,0,0 }, 5, 0.3);
	RBsys->addToForceRegistry(rbWhirlL3_1, ball);

	rbWindL3_0 = new WindRBFG(false, { 0,50,0 }, windPos_0, windRadius, { 0,1,0,0 }, 18, 2);
	rbWindL3_1 = new WindRBFG(false, { 0,50,0 }, windPos_1, windRadius, { 0,1,0,0 }, 18, 2);
	rbWindL3_2 = new WindRBFG(false, { 0,50,0 }, windPos_2, windRadius, { 0,1,0,0 }, 18, 2);
	RBsys->addToForceRegistry(rbWindL3_0, ball); RBsys->addToForceRegistry(rbWindL3_1, ball);
	RBsys->addToForceRegistry(rbWindL3_2, ball);

	//creamos los generadores de partículas
	fuenteWhirlL3_0 = new UniformParticleGenerator("FuenteWhirlWindL3_0", { whirlPos_0.x, whirlPos_0.y - 50, whirlPos_0.z }, Vector3(0, 2, 0), { 1,0,0,1 }, 1, baseParticle, { 100,0.1,100 }, { 3,8,3 }, 2, 4);
	particleWhirlL3_0 = new WhirlwindForceGenerator(false, whirlPos_0, whirlRadius, { 1,0,0,0 }, 0.6);
	fuenteWhirlL3_0->addForceGenerator(earthGravity); fuenteWhirlL3_0->addForceGenerator(particleWhirlL3_0);
	PSys->addParticleGenerator(fuenteWhirlL3_0);
	fuenteWhirlL3_1 = new UniformParticleGenerator("FuenteWhirlWindL3_1", { whirlPos_1.x, whirlPos_1.y - 50, whirlPos_1.z }, Vector3(0, 2, 0), { 1,0,0,1 }, 1, baseParticle, { 100,0.1,100 }, { 3,8,3 }, 2, 4);
	particleWhirlL3_1 = new WhirlwindForceGenerator(false, whirlPos_1, whirlRadius, { 1,0,0,0 }, 0.6);
	fuenteWhirlL3_1->addForceGenerator(earthGravity); fuenteWhirlL3_1->addForceGenerator(particleWhirlL3_1);
	PSys->addParticleGenerator(fuenteWhirlL3_1);

	float wr = (float)windRadius - 30;
	fuenteWindL3_0 = new UniformParticleGenerator("fuenteWindL3_0", { windPos_0.x,0,windPos_0.z }, Vector3(0, 15, 0), { 0,1,0,1 }, 1, baseParticle, { wr,0.1,wr }, { 3,0.1,3 }, 0.6, 15);
	fuenteWindL3_1 = new UniformParticleGenerator("fuenteWindL3_1", { windPos_1.x,0,windPos_1.z }, Vector3(0, 15, 0), { 0,1,0,1 }, 1, baseParticle, { wr,0.1,wr }, { 3,0.1,3 }, 0.6, 15);
	fuenteWindL3_2 = new UniformParticleGenerator("fuenteWindL3_2", { windPos_2.x,0,windPos_2.z }, Vector3(0, 15, 0), { 0,1,0,1 }, 1, baseParticle, { wr,0.1,wr }, { 3,0.1,3 }, 0.6, 15);
	particleWindL3_0 = new WindForceGenerator(false, { 0,12,0 }, windPos_0, windRadius * 2, { 0,1,0,0 }, 1, 0.01);
	particleWindL3_1 = new WindForceGenerator(false, { 0,12,0 }, windPos_1, windRadius * 2, { 0,1,0,0 }, 1, 0.01);
	particleWindL3_2 = new WindForceGenerator(false, { 0,12,0 }, windPos_2, windRadius * 2, { 0,1,0,0 }, 1, 0.01);
	//añadimos todo al sistema
	fuenteWindL3_0->addForceGenerator(smokeGravity);	fuenteWindL3_0->addForceGenerator(particleWindL3_0);
	fuenteWindL3_1->addForceGenerator(smokeGravity);	fuenteWindL3_2->addForceGenerator(particleWindL3_1);
	fuenteWindL3_2->addForceGenerator(smokeGravity);	fuenteWindL3_1->addForceGenerator(particleWindL3_2);

	PSys->addParticleGenerator(fuenteWindL3_0); PSys->addParticleGenerator(fuenteWindL3_1);
	PSys->addParticleGenerator(fuenteWindL3_2);

}
void Scene::releaseLevel3() {
	releaseDefault();
	for (auto o : level3Rocks) {
		o->setPos({ -800,-800,-800 });
		o->actualiza();
		auto rd = o->_rigidStatic();
		gScene->removeActor(*rd);
		delete o;
	}
	level3Rocks.clear();
	//eliminar los generadores de particulas
	delete rbWhirlL3_0; delete particleWhirlL3_0; delete fuenteWhirlL3_0;
	delete rbWhirlL3_1; delete particleWhirlL3_1; delete fuenteWhirlL3_1;
	delete rbWindL3_0; delete rbWindL3_1; delete rbWindL3_2;
	delete particleWindL3_0; delete particleWindL3_1; delete particleWindL3_2;
	delete fuenteWindL3_0; delete fuenteWindL3_1; delete fuenteWindL3_2;
}
void Scene::updateLevel3(double t) {
	updateDefault(t);

}
void Scene::keyLevel3(std::map<char, bool> keyboard, std::map<int, bool> mouse) {
	keyDefault(keyboard, mouse);

}
void Scene::onCollisionLevel3(physx::PxActor* actor1, physx::PxActor* actor2) {
	;
}
#pragma endregion
