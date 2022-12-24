#pragma once

#include "RadialShotGenerator.h"

class Shotgun : public RadialShotGenerator {

public:
	Shotgun(physx::PxPhysics* gp, Camera* cam, bool* shoot);
protected:
};