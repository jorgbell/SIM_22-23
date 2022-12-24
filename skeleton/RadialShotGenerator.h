#pragma once
#include "RBShootGenerator.h"

/*
Clase que genera el disparo de una escopeta, formando una circunferencia de nVertices
Si ponemos pocos vertices, generamos otras formas (ej: 3 vertices = triangulo)
*/
class RadialShotGenerator :
	public RBShootGenerator{
public:
	RadialShotGenerator(std::string name, physx::PxPhysics* gp, Camera* cam, Vector4 color,
		bool* shoot, double radius, int nVertex, float force, float cooldown, float timeBetween, int nDisparos,
		double mass, double damp, double life);
protected:
	virtual list<DynamicRigidBody*> shoot() override;
	double _radius;
	float _force;
};