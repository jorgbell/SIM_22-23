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
	_particleForceRegistry.updateForces(t);
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
		if (g->getParticleGeneratorName() == name)
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
		if (g->getParticleGeneratorName() == name)
			encontrado = true;
		else
			it++;
	}

	if (encontrado) {
		auto lfg = (*it)->getForceGenerators();
		for (auto fg : lfg) {
			_particleForceRegistry.deleteParticleRegistry(fg);
		}
		_generatorsPool.erase(it);
	}
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
		if (p->isDead()) {
			//eliminará la particula en caso de que o haya pasado su tiempo de vida o haya salido de la zona de interes
			_particleForceRegistry.deleteParticleRegistry(p);
			delete(*it);
			it = _particlePool.erase(it);
		}
		else
			it++;
	}

	//creacion de las nuevas particulas
	for (auto g : _generatorsPool) {
		auto l = g->generateParticles();
		auto lfg = g->getForceGenerators();
		for (auto p : l) {
			_particlePool.push_back(p);
			//añade las particulas al registro de fuerzas.
			//cada generador de particulas tiene generadores de fuerzas asociados, y añadira todas sus particulas generadas junto con esos generadores de particulas
			for (auto fg : lfg) {
				_particleForceRegistry.addRegistry(fg, p);
			}
		}
	}
	
}
