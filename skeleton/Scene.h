#pragma once
#include <ctype.h>
#include <stack>
#include <iostream>
#include "RenderUtils.hpp"
#include "callbacks.hpp"
using namespace physx;

class Scene {
public:
	Scene(PxPhysics* gPhys, PxScene* gSc, PxMaterial* gMat, Camera* cam, std::stack<Scene*> sceneManager, std::string name);
	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void update(double t) = 0;
	virtual void keyPress(unsigned char key) = 0;
	
	//getters
	std::string _id() { return id; }

private:
	PxPhysics* gPhysics;
	PxScene* gScene;
	PxMaterial* gMaterial;

	Camera* camera;

	std::string id = "";
	std::stack<Scene*> sceneManager;


};