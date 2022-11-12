#include "FireworksSystem.h"
#include <iostream>

FireworksSystem::FireworksSystem(int maxExplosions) : maxFireworksGeneration(maxExplosions), nExplosions(0)
{
	nExplosions = 0;
	_fireworksGen = new FireworksGenerator();
}

void FireworksSystem::startFire(Vector3 initPos, Vector3 initVel, FireworksType type) {
	//generación de la primera particula. Actuará de base para el generador.
	//solo funcionará si no hay particulas en pantalla
	if (_particlePool.size() == 0) {
		if (!dynamic_cast<Firework*>(_fireworksGen->getBaseParticle())) {
			_fireworksGen->setBaseParticle(new Firework());
		}
		Firework* first = dynamic_cast<Firework*>(_fireworksGen->getBaseParticle()->clone());
		first->setType(type); first->setPos(initPos); first->setVel(initVel);
		_particlePool.push_back(first);
	}
}

FireworksSystem::~FireworksSystem()
{
	auto lfg = _fireworksGen->getForceGenerators();
	while (!lfg.empty()) {
		auto fg = lfg.back();
		lfg.pop_back();
		delete fg;
	}
	delete _fireworksGen;
}

void FireworksSystem::update(double t)
{
	checkParticles();
	//idealmente, este sistema de particulas no tendrá otros sistemas asociados
	//por lo tanto, en el update de ParticleSystem no se generarán nuevas particulas por no tener esos sistemas
	//no obstante, cabe la posibilidad de que se pueda
	_particleForceRegistry.updateForces(t);
	for (auto p : _particlePool)
		p->integrate(t);
}

void FireworksSystem::checkParticles()
{

	list<Particle*>::iterator it;
	std::list<Particle*> explosions;
	//comprueba si han muerto fireworks. En caso de morir, podrá generar nuevas particulas.
	for (it = _particlePool.begin(); it != _particlePool.end();) {
		Firework* f = dynamic_cast<Firework*>(*it);
		if (f != nullptr && f->isDead()) {
			//GENERARA UNA EXPLOSION SI ES UN FIREWORK DE TIPO >0 Y SI QUEDAN EXPLOSIONES POSIBLES
			if (f->getFireworkType() != FIREWORK_0 && nExplosions <= maxFireworksGeneration) {
				//indicamos al generador cual ha sido la particula que ha explotado, para conseguir sus payloads y posicion actual
				_fireworksGen->setLastExploded(f);
				//generamos particulas nuevas, algunas serán de tipo >0, el resto, de tipo 0
				auto list = _fireworksGen->generateParticles();
				for (auto a : list) {
					explosions.push_back(a);
				}
				nExplosions += 1;
			}

			_particleForceRegistry.deleteParticleRegistry(*it);
			delete (*it);
			it = _particlePool.erase(it);
			//eliminará la particula en cualquier caso
			f = nullptr;
		}
		else //si no ha muerto comprueba la siguiente
			it++;
	}

	auto lfg = _fireworksGen->getForceGenerators();
	//añadira todas las nuevas particulas
	for (Particle* p : explosions) {
		_particlePool.push_back(p);
		//añade las particulas al registro de fuerzas.
		//cada generador de particulas tiene generadores de fuerzas asociados, y añadira todas sus particulas generadas junto con esos generadores de particulas
		for (auto fg : lfg) {
			_particleForceRegistry.addRegistry(fg, p);
		}
	}
}

