#pragma once
#include "ForceGenerator.h"
class ExplosionForceGenerator :
    public ForceGenerator
{
public:

	ExplosionForceGenerator(const Vector3& pos, const Vector4& regionColor, double force, double size, double tconst, bool* exploded);
	~ExplosionForceGenerator();

	virtual void updateForce(Particle* particle, double t);

private:
	double intensity;
	double regionRadius;
	double timeConstant;
	bool* hasExploded;

	Transform regionTransform;
	RenderItem* region;

	bool collides(const Vector3& pos);
};

