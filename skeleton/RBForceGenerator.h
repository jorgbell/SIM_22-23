#pragma once
#include "Static_Dynamic_Body.h"
#include <list>
#include <string>
class RBForceGenerator
{
public:
	virtual void updateForce(DynamicRigidBody* rb, double duration) = 0;
	std::string _name;
	double t = -1e10; //if starting negative --> eternal

}

;

