#pragma once
#include "RBShootGenerator.h"

/*
Clase que genera el disparo de una escopeta, formando una circunferencia de nVertices
Si ponemos pocos vertices, generamos otras formas (ej: 3 vertices = triangulo)
*/
class Shotgun : 
	public RBShootGenerator{
public:
	Shotgun(physx::PxPhysics* gp, Camera* cam, bool* shoot, double radius, int nVertex);

protected:
	virtual list<DynamicRigidBody*> shoot() override;
	double _radius;
};