#pragma once
#include "Scene.h"
class P5Scene : public Scene
{
public:
	P5Scene(PxFoundation* gFoundation, PxPvd* gPvd, std::stack<Scene*> sceneManager);
	// Heredado vía Scene
	virtual void Init() override;
	virtual void Release() override;
	virtual void update(double t) override;
	virtual void keyPress(unsigned char key) override;
	virtual void onCollision(physx::PxActor* actor1, physx::PxActor* actor2) override;
private:
	

};

