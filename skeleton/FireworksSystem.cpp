#include "FireworksSystem.h"

FireworksSystem::FireworksSystem(int maxExplosions) : maxFireworksGeneration(maxExplosions)
{
	_fireworksGen = new FireworksGenerator();
	nExplosions = 0;
}

FireworksSystem::~FireworksSystem()
{
	while (!_fireworksPool.empty()) {
		auto f = _fireworksPool.back();
		_fireworksPool.pop_back();
		delete f;
	}
	delete _fireworksGen;
}

void FireworksSystem::update(double t)
{
	checkParticles();
	//idealmente, este sistema de particulas no tendrá otros sistemas asociados
	//por lo tanto, en el update de ParticleSystem no se generarán nuevas particulas por no tener esos sistemas
	//no obstante, cabe la posibilidad de que se pueda
	for (auto p : _particlePool)
		p->integrate(t);

}

void FireworksSystem::checkParticles()
{
	//este metodo realizara el funcionamiento del update
	//comprueba si los fireworks han muerto para explotar
	//si explota, devuelve fireworks en caso de poder hacerlo (quedan iteraciones)
	//cuando explota, devuelve un vector de fireworks y de particulas normales
	//las particulas normales las añade al vector normal y las fireworks al de fireworks

	list<Particle*>::iterator it;

	for (it = _particlePool.begin(); it != _particlePool.end();) {
		//TODO: Hacer casteo a firework
		Particle* f = (*it);
		if (f != nullptr && f->isDead()) {
			//si el firework se ha muerto, explota antes de morir, creando nuevos fireworks y nuevas particulas
			//añade los fireworks nuevos a la lista
			if (nExplosions <= maxFireworksGeneration) {
				for (auto f : _fireworksGen->generateFireworks(f->getPayloads()))
					_particlePool.push_back(f);
				nExplosions += 1;
			}
			//eliminará la particula en caso de que o haya pasado su tiempo de vida o haya salido de la zona de interes
			it = _particlePool.erase(it);
			delete(f);
		}
		else
			it++;
	}

}

