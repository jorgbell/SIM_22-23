#include "Scene.h"


Scene::Scene(PxPhysics* gPhys, PxScene* gSc, PxMaterial* gMat, Camera* cam, std::stack<Scene*> sMng, std::string name) :
	gPhysics(gPhys), gScene(gSc), gMaterial(gMat), id(name), sceneManager(sMng)
{
	
}
