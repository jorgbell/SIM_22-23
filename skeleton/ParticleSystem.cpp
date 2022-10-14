#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
}

void ParticleSystem::update(double t)
{
	checkParticles(); 
	for (auto p : _particlePool)
		p->integrate(t);
	for (auto g : _generatorsPool)
		g->generateParticles();
}

/*
	Devuelve el primer generador que encuentre que sea del tipo indicado.
*/

ParticleGenerator* ParticleSystem::getParticleGenerator(string name)
{
	bool encontrado = false;
	list<ParticleGenerator*>::iterator it = _generatorsPool.begin();

	while (!encontrado && it != _generatorsPool.end()) {
		if()
	}
	return nullptr;
}

/*
	Método para el mantenimiento de las partículas. Mata las partículas que se hayan marcado en el frame anterior
	como partículas muertas.
*/
void ParticleSystem::checkParticles()
{
	list<Particle*>::iterator it;
	for (it = _particlePool.begin(); it != _particlePool.end();) {
		Particle* p = (*it);
		if (p != nullptr && p->isDead()) {
			//eliminará la particula en caso de que o haya pasado su tiempo de vida o haya salido de la zona de interes
			it = _particlePool.erase(it);
			delete(p);
		}
		else
			it++;
	}
}
