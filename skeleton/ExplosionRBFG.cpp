#include "ExplosionRBFG.h"
#include <cmath>

ExplosionRBFG::ExplosionRBFG(const Vector3& pos, const Vector4& regionColor, double force, double size, double tconst, bool* exploded) :
	intensity(force), regionRadius(size), timeConstant(tconst), hasExploded(exploded)
{
	regionTransform = Transform(pos);
	region = new RenderItem(CreateShape(physx::PxSphereGeometry(regionRadius)), &regionTransform, regionColor);
}

ExplosionRBFG::~ExplosionRBFG()
{
	region->release();
}

void ExplosionRBFG::updateForce(DynamicRigidBody* rb, double t)
{
	if (!(*hasExploded))
		return;
	//Check that the particle has Finite mass
	if (fabs(rb->getInverseMass()) < 1e-10 || !collides(rb->getPos()))
		return;
	Vector3 p = rb->getPos();
	Vector3 c = regionTransform.p;
	Vector3 diff = p - c;
	//𝑟=√(𝑥−𝑥𝑐)2+(𝑦−𝑦𝑐)2+(𝑧−𝑧𝑐)2
	double r = sqrt((diff.x * diff.x + diff.y * diff.y + diff.z * diff.z));

	if (r >= regionRadius)
		return;

	double kr = intensity / r * r; //𝐾/𝑟2
	double ett = std::exp(-t / timeConstant); //𝑒(−𝑡/𝜏)
	Vector3 force = kr * diff * ett;

	rb->addForce(force);


}

bool ExplosionRBFG::collides(const Vector3& pos) {
	return (regionTransform.p - pos).magnitude() < regionRadius;

}
