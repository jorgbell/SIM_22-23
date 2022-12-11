#include "RBSystem.h"

RBSystem::~RBSystem() {
	while (!_rbPool.empty()) {
		auto rb = _rbPool.back();
		_rbPool.pop_back();
		auto rd = rb->_rigidDynamic();
		_gScene->removeActor(*rd);
		delete rb;
	}
}

void RBSystem::update(double t)
{
	checkRB();
	_rbForceRegistry.updateForces(t);
	for (auto rb : _rbPool)
		rb->update(t);

}

/*
	Devuelve el primer generador que encuentre que sea del tipo indicado.
*/

RBGenerator* RBSystem::getParticleGenerator(string name)
{
	bool encontrado = false;
	list<RBGenerator*>::iterator it = _generatorsPool.begin();
	RBGenerator* g;

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
void RBSystem::erase(string name)
{
	bool encontrado = false;
	list<RBGenerator*>::iterator it = _generatorsPool.begin();
	RBGenerator* g;

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
			_rbForceRegistry.deleteParticleRegistry(fg);
		}
		_generatorsPool.erase(it);
	}
}

/*
	Método para el mantenimiento de las partículas. Mata las partículas que se hayan marcado en el frame anterior
	como partículas muertas.
*/
void RBSystem::checkRB()
{
	list<DynamicRigidBody*>::iterator it;
	for (it = _rbPool.begin(); it != _rbPool.end();) {
		DynamicRigidBody* rb = (*it);
		if (rb->isDead()) {
			//eliminará la particula en caso de que o haya pasado su tiempo de vida o haya salido de la zona de interes
			_rbForceRegistry.deleteParticleRegistry(rb);
			delete(*it);
			it = _rbPool.erase(it);
		}
		else
			it++;
	}

	//creacion de las nuevas particulas
	for (auto g : _generatorsPool) {
		auto l = g->generateParticles();
		auto lfg = g->getForceGenerators();
		for (auto p : l) {
			addToParticlePool(p);
			//añade las particulas al registro de fuerzas.
			//cada generador de particulas tiene generadores de fuerzas asociados, y añadira todas sus particulas generadas junto con esos generadores de particulas
			for (auto fg : lfg) {
				_rbForceRegistry.addRegistry(fg, p);
			}
		}
	}

}
