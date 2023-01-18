#pragma once
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Particle.h"
using namespace physx;
class Player {
public:
	Player(Camera* cam, Particle* body, bool* jetpack):_camera(cam), _body(body), _jetpackBool(jetpack) {};
	void update(double t) {
		clampPosition();
		_camera->setY(_body->getPos().y);
	}
	void stop() { if(_body->getVel().y <0)_body->setVel({0,0,0}); }
private:
	void clampPosition() {
		//altura
		if (_body->getPos().y < 12)
			_body->setPos({ _body->getPos().x,12.01, _body->getPos().z });
		//bordes del mapa

	}
	Camera* _camera;
	Particle* _body;
	bool* _jetpackBool;
};