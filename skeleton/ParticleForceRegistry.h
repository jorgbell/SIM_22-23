#pragma once

#include <map>
#include "ForceGenerator.h"

typedef std::pair<ForceGenerator*, Particle*> FRPair_P;

class ParticleForceRegistry : public std::multimap<ForceGenerator*, Particle*> {
public:
	void updateForces(double duration) {
		for (auto it = begin(); it != end(); it++) {
			it->first->updateForce(it->second, duration);
		}
	}

	void addRegistry(ForceGenerator* fg, Particle* p) {
		insert(FRPair_P( fg, p ));
	}

	void deleteParticleRegistry(Particle* p) {
		//borra una particula concreta de la lista de generadores de fuerzas, para que no se le aplique m�s
		bool encontrado = false;
		auto it = begin();

		while (it != end()) {
			if (it->second == p) {
				it = erase(it);
			}
			else
				it++;
		}
	}

	void deleteParticleRegistry(ForceGenerator* fg) {
		auto it = find(fg);
		//borra de la lista todas las particulas asociadas a este generador de fuerza, ademas de borrar la key en si del generador de fuerzas
		if(it != end())
			erase(fg);
	}

};


