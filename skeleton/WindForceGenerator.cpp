#include "WindForceGenerator.h"
#include <iostream>
WindForceGenerator::WindForceGenerator(bool render, const Vector3& windVel, const Vector3& windPos, double r, const Vector4& color, float k1, float k2) :
	_k1(k1), _k2(k2), regionRadius(r)
{
	regionTransform = Transform(windPos);
	if(render) region = new RenderItem(CreateShape(physx::PxSphereGeometry(regionRadius)), &regionTransform, color);
	setWindVel(windVel);
}

WindForceGenerator::~WindForceGenerator() {
	if(region!=nullptr) region->release();
}

void WindForceGenerator::updateForce(Particle* particle, double t)
{
	/*
	En ese caso, la fuerza ejercida por el viento dependerá de la diferencia de velocidades del viento con  respecto  a  la
	velocidad  de  la  partícula  en  el  punto.
	Una  aproximación  podría  ser hacerlo proporcional a dicha diferencia:
	*/

	//Check that the particle has Finite mass
	if (fabs(particle->getInverseMass()) < 1e-10 || !collides(particle->getPos()))
		return;
	Vector3 diff = _windVelocity - particle->getVel(); //(Vv - V)

	Vector3 aux = _k1 * diff;  //k1*(Vv-V)
	Vector3 aux2 = _k2 * diff.magnitude() * diff; //K2*||Vv-v||*(Vv-v)
	aux += aux2;//Fv = k1*(Vv-V) + k2*||Vv-v||*(Vv-v)

	particle->addForce(aux);

}

bool WindForceGenerator::collides(const Vector3& pos) {
	return (regionTransform.p - pos).magnitude() < regionRadius;

}