#include "FireworksSystem.h"

FireworksSystem::FireworksSystem(Firework* first, int maxExplosions) : maxFireworksGeneration(maxExplosions), nExplosions(0)
{
	nExplosions = 0;
	//generaci�n de la primera particula. Actuar� de base para el generador.
	_particlePool.push_back(first);
	_fireworksGen = new FireworksGenerator(first);
}

FireworksSystem::~FireworksSystem()
{
	delete _fireworksGen;
}

void FireworksSystem::update(double t)
{
	checkParticles();
	//idealmente, este sistema de particulas no tendr� otros sistemas asociados
	//por lo tanto, en el update de ParticleSystem no se generar�n nuevas particulas por no tener esos sistemas
	//no obstante, cabe la posibilidad de que se pueda
	for (auto p : _particlePool)
		p->integrate(t);

}

void FireworksSystem::checkParticles()
{

	list<Particle*>::iterator it;
	std::list<Particle*> explosions;
	//comprueba si han muerto fireworks. En caso de morir, podr� generar nuevas particulas.
	for (it = _particlePool.begin(); it != _particlePool.end();) {
		Firework* f = static_cast<Firework*>(*it);
		if (f != nullptr && f->isDead()) {
			//GENERARA UNA EXPLOSION SI ES UN FIREWORK DE TIPO >0 Y SI QUEDAN EXPLOSIONES POSIBLES
			if (f->getFireworkType() != FIREWORK_0 && nExplosions <= maxFireworksGeneration) {
				//indicamos al generador cual ha sido la particula que ha explotado, para conseguir sus payloads y posicion actual
				_fireworksGen->setLastExploded(f);
				//generamos particulas nuevas, algunas ser�n de tipo >0, el resto, de tipo 0
				auto list = _fireworksGen->generateParticles();
				for (auto a : list) {
					explosions.push_back(a);
				}
				nExplosions += 1;
			}
			
			//eliminar� la particula en cualquier caso
			it = _particlePool.erase(it);
			delete(f);
		}
		else //si no ha muerto comprueba la siguiente
			it++;
	}

	//a�adira todas las nuevas particulas
	for (Particle* p : explosions) {
		_particlePool.push_back(p);
	}

}

