#include "Shotgun.h"

Shotgun::Shotgun(physx::PxPhysics* gp, Camera* cam,	bool* shoot)
	:RadialShotGenerator("Shotgun", gp, cam, /*color*/{0.5,0.1,0.8,1}, shoot, 
		/*radius*/2, /*numBalas*/3, /*force*/150, /*cooldown*/2, /*timeBetween*/0, /*numDisparos*/1, 
		/*masa*/2.0, /*damping*/0.75, /*life*/2) {
}