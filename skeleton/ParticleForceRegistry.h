#pragma once

#include <map>
#include "ForceGenerator.h"

typedef std::pair<ForceGenerator*, Particle*> FRPair;

class ParticleForceRegistry : public std::multimap<ForceGenerator*, Particle*> {
public:
	void updateForces(double duration) {
		for (auto it = begin(); it != end(); it++) {
			it->first->updateForce(it->second, duration);
		}
	}

	void addRegistry(ForceGenerator* fg, Particle* p) {
		insert(FRPair( fg, p ));
	}

	void deleteParticleRegistry(Particle* p) {
		//borra una particula concreta de la lista de generadores de fuerzas, para que no se le aplique más
		bool encontrado = false;
		auto it = begin();

		while (!encontrado && it != end()) {
			if (it->second == p) {
				auto r = (*it);
				erase(it);
				//delete de la fuerza? TODO
				encontrado = true;
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


