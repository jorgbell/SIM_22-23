#include "BuoyancyFG.h"

BuoyancyFG::BuoyancyFG(float h, float V, float d, Vector3 liquid_pos) :
	_height(h), _volume(V), _liquid_density(d) 
{
	_liquid_particle = new Particle(liquid_pos, { 0,0,0 }, { 0,0,0 });
	_liquid_particle->setMass(1e6);
	_liquid_particle->setColor({ 0,0,1,1 });
	_liquid_particle->setShape(CreateShape(physx::PxBoxGeometry(15, 0.1, 15)));
}

BuoyancyFG::~BuoyancyFG() {
	delete _liquid_particle;
}

void BuoyancyFG::updateForce(Particle* particle, double t) {
	float h = particle->getPos().y;
	float h0 = _liquid_particle->getPos().y;

	Vector3 f(0, 0, 0);
	float inmersed = 0.0;

	if (h - h0 > _height * 0.5) {
		inmersed = 0.0;
	}
	else if (h0 - h > _height * 0.5) {
		//totally inmersed
		inmersed = 1.0;
	}
	else {
		inmersed = (h0 - h) / _height + 0.5;
	}

	f.y = _liquid_density * _volume * inmersed*9.8;

	particle->addForce(f*particle->getMass());
}