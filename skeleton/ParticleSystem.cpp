#include "ParticleSystem.h"

ParticleSystem::~ParticleSystem() {
	while (!_particlePool.empty()) {
		auto p = _particlePool.back();
		_particlePool.pop_back();
		delete p;
	}
}

void ParticleSystem::update(double t)
{
	checkParticles();
	for (auto p : _particlePool)
		p->integrate(t);
	
}

/*
	Devuelve el primer generador que encuentre que sea del tipo indicado.
*/

ParticleGenerator* ParticleSystem::getParticleGenerator(string name)
{
	bool encontrado = false;
	list<ParticleGenerator*>::iterator it = _generatorsPool.begin();
	ParticleGenerator* g;

	while (!encontrado && it != _generatorsPool.end()) {
		g = (*it);
		if (g->getGeneratorName() == name)
			encontrado = true;
		else
			it++;
	}

	if (!encontrado)
		return nullptr;
	return g;
}

/*
	elimina de la lista de generadores para que no siga generando más de dicho generador.
	no borra memoria, simplemente dejará de hacer el integrate con dicho generador.
*/
void ParticleSystem::erase(string name)
{
	bool encontrado = false;
	list<ParticleGenerator*>::iterator it = _generatorsPool.begin();
	ParticleGenerator* g;

	while (!encontrado && it != _generatorsPool.end()) {
		g = (*it);
		if (g->getGeneratorName() == name)
			encontrado = true;
		else
			it++;
	}

	if (encontrado)
		_generatorsPool.erase(it);
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

	//creacion de las nuevas particulas
	for (auto g : _generatorsPool) {
		auto l = g->generateParticles();
		for (auto p : l)
			_particlePool.push_back(p);
	}
}
