#include "ExplosionForceGenerator.h"

ExplosionForceGenerator::ExplosionForceGenerator(const Vector3& pos, const Vector4& regionColor, double force, double size, double tconst, bool* exploded) :
	intensity(force), regionRadius(size), timeConstant(tconst), hasExploded(exploded)
{
	regionTransform = Transform(pos);
	region = new RenderItem(CreateShape(physx::PxSphereGeometry(regionRadius)), &regionTransform, regionColor);
}

ExplosionForceGenerator::~ExplosionForceGenerator()
{
	region->release();
}

void ExplosionForceGenerator::updateForce(Particle* particle, double t)
{
	if (!(*hasExploded))
		return;
	//Check that the particle has Finite mass
	if (fabs(particle->getInverseMass()) < 1e-10 || !collides(particle->getPos()))
		return;
	Vector3 p = particle->getPos();
	Vector3 c = regionTransform.p;
	//𝑟=√(𝑥−𝑥𝑐)2+(𝑦−𝑦𝑐)2+(𝑧−𝑧𝑐)2
	double r = std::sqrt(std::pow(p.x - c.x, 2) + std::pow(p.y - c.y, 2) + std::pow(p.z - c.z, 2));
	
	if (r >= regionRadius)
		return;
	
	double kr = intensity / std::pow(r, 2); //𝐾/𝑟2
	double etr = std::exp(-1 * (t / timeConstant)); //𝑒(−𝑡/𝜏)
	Vector3 diff = particle->getPos() - regionTransform.p;
	Vector3 force = kr * diff * etr;

	particle->addForce(force * particle->getMass());
}

bool ExplosionForceGenerator::collides(const Vector3& pos) {
	return (regionTransform.p - pos).magnitude() < regionRadius;

}
