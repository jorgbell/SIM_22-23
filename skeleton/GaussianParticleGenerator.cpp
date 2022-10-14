#include "GaussianParticleGenerator.h"

GaussianParticleGenerator::GaussianParticleGenerator(Vector3 pos, Vector3 vel, int n, Particle* b, double prob, string t) : ParticleGenerator(pos, vel, n, b, prob, t)
{
}

list<Particle*> GaussianParticleGenerator::generateParticles()
{
	list<Particle*> particles;

	for (int i = 0; i < _nParticles; i++)
		particles.push_back(_baseParticle->clone());

	return particles;
}
