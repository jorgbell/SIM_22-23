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
	elimina de la lista de generadores para que no siga generando m�s de dicho generador.
	no borra memoria, simplemente dejar� de hacer el integrate con dicho generador.
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
	M�todo para el mantenimiento de las part�culas. Mata las part�culas que se hayan marcado en el frame anterior
	como part�culas muertas.
*/
void ParticleSystem::checkParticles()
{
	list<Particle*>::iterator it;
	for (it = _particlePool.begin(); it != _particlePool.end();) {
		Particle* p = (*it);
		if (p->isDead()) {
			//eliminar� la particula en caso de que o haya pasado su tiempo de vida o haya salido de la zona de interes
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
			//a�ade las particulas al registro de fuerzas.
			//cada generador de particulas tiene generadores de fuerzas asociados, y a�adira todas sus particulas generadas junto con esos generadores de particulas
			for (auto fg : lfg) {
				_particleForceRegistry.addRegistry(fg, p);
			}
		}
	}
	
}
