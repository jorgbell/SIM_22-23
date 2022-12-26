#include "WindRBFG.h"
#include <iostream>
WindRBFG::WindRBFG(const Vector3& windVel, const Vector3& windPos, double r, const Vector4& color, float k1, float k2) :
	_k1(k1), _k2(k2), regionRadius(r)
{
	regionTransform = Transform(windPos);
	region = new RenderItem(CreateShape(physx::PxSphereGeometry(regionRadius)), &regionTransform, color);
	setWindVel(windVel);
}

WindRBFG::~WindRBFG() {
	region->release();
}

void WindRBFG::updateForce(DynamicRigidBody* rb, double t)
{
	/*
	En ese caso, la fuerza ejercida por el viento dependerá de la diferencia de velocidades del viento con  respecto  a  la
	velocidad  de  la  partícula  en  el  punto.
	Una  aproximación  podría  ser hacerlo proporcional a dicha diferencia:
	*/

	//Check that the particle has Finite mass
	if (fabs(rb->getInverseMass()) < 1e-10 || !collides(rb->getPos()))
		return;
	Vector3 diff = _windVelocity - rb->getVel(); //(Vv - V)

	Vector3 aux = _k1 * diff;  //k1*(Vv-V)
	Vector3 aux2 = _k2 * diff.magnitude() * diff; //K2*||Vv-v||*(Vv-v)
	aux += aux2;//Fv = k1*(Vv-V) + k2*||Vv-v||*(Vv-v)

	rb->addForce(aux);

}

bool WindRBFG::collides(const Vector3& pos) {
	return (regionTransform.p - pos).magnitude() < regionRadius;

}