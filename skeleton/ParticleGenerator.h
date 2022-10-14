#pragma once
#include "Particle.h"
#include <list>
using namespace std;

class ParticleGenerator {
public:
	ParticleGenerator(Vector3 pos, Vector3 vel, int n) :
		_origin(pos), _velMedia(vel), _nParticles(n){}

	void update(float t) {
		//MANTENIMIENTO DE PARTICULAS
		checkParticles(); //mata las particulas que tenga que matar
		for (Particle* p : _pool) 
			p->integrate(t); //integra el resto de particulas
		//GENERACION DE PARTICULAS

	}
	virtual void generateParticles() = 0 {};

protected:
	list<Particle*> _pool;
	Vector3 _origin;
	Vector3 _velMedia;
	int _nParticles;
	inline bool checkLifeTime(Particle* p) {
		//elimina la particula si ha superado el tiempo de vida, 
		//y solo si no tiene el valor maximo a -1 (queremos que no se elimine hasta el final del programa)
		return p != nullptr && p->isDead();
	}
	inline bool checkInZone(Particle* p) { 
		//elimina la particula si su posicion está fuera del rango especificado (TODO)
		return false;
	}
	void checkParticles() {
		list<Particle*>::iterator it;
		for (it = _pool.begin(); it != _pool.end();) {
			Particle* p = (*it);
			if (checkLifeTime(p) || checkInZone(p)) {
				//eliminará la particula en caso de que o haya pasado su tiempo de vida o haya salido de la zona de interes
				it = _pool.erase(it);
				delete(p);
			}
			else
				it++;
		}
	}
};