#pragma once
#include "RBForceGenerator.h"
class ExplosionRBFG :
	public RBForceGenerator
{
public:

	ExplosionRBFG(const Vector3& pos, const Vector4& regionColor, double force, double size, double tconst, bool* exploded);
	~ExplosionRBFG();

	virtual void updateForce(DynamicRigidBody* rb, double t);

private:
	double intensity;
	double regionRadius;
	double timeConstant;
	bool* hasExploded;

	Transform regionTransform;
	RenderItem* region;

	bool collides(const Vector3& pos);
};

