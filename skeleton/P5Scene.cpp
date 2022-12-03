#include "P5Scene.h"

P5Scene::P5Scene(PxFoundation* gFoundation, PxPvd* gPvd, std::stack<Scene*> sceneManager):
	Scene(gFoundation, gPvd, sceneManager, "Practica_5")
{

}

void P5Scene::Init()
{
}

void P5Scene::Release()
{
}

void P5Scene::update(double t)
{
}

void P5Scene::keyPress(unsigned char key)
{
}

void P5Scene::onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
}
