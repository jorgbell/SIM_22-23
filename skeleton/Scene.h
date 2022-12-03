#pragma once
#include <ctype.h>
#include <iostream>
#include "RenderUtils.hpp"
#include "callbacks.hpp"
using namespace physx;

class Scene {
public:
	Scene(PxFoundation* gFoundation, PxPvd* gPvd, std::string name);
	void Init();
	void Release();
	void update(double t);
	void stepPhysics(bool interactive, double t);
	void cleanupPhysics(bool interactive);
	void keyPress(unsigned char key);
	void onCollision(physx::PxActor* actor1, physx::PxActor* actor2);


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



};