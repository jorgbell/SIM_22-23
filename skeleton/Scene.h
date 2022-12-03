#pragma once
#include <ctype.h>
#include <stack>
#include <iostream>
#include "RenderUtils.hpp"
#include "callbacks.hpp"
using namespace physx;

class Scene {
public:
	Scene(PxFoundation* gFoundation, PxPvd* gPvd, std::stack<Scene*> sceneManager, std::string name);
	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void update(double t) = 0;
	virtual void keyPress(unsigned char key) = 0;
	virtual void onCollision(physx::PxActor* actor1, physx::PxActor* actor2) = 0;
	
	void stepPhysics(bool interactive, double t);
	void cleanupPhysics(bool interactive);


	//getters
	PxPhysics* _gPhysics() { return gPhysics; };
	PxScene* _gScene() { return gScene; };
	PxDefaultCpuDispatcher* _gDispatcher() { return gDispatcher; };
	ContactReportCallback _gContactReportCallback() { return gContactReportCallback; };
	std::string _id() { return id; }
	PxMaterial* _gMaterial() { return actualMaterial; };

private:
	PxPhysics* gPhysics = NULL;
	PxScene* gScene = NULL;
	PxDefaultCpuDispatcher* gDispatcher;
	ContactReportCallback gContactReportCallback;
	PxFoundation* gFoundation = NULL;
	PxPvd* gPvd = NULL;
	std::string id = "";
	PxMaterial* actualMaterial;
	std::stack<Scene*> sceneManager;


};