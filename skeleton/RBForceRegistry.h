#pragma once

#include <map>
#include "RBForceGenerator.h"

typedef std::pair<RBForceGenerator*, DynamicRigidBody*> FRPair;

class RBForceRegistry : public std::multimap<RBForceGenerator*, DynamicRigidBody*> {
public:
	void updateForces(double duration) {
		for (auto it = begin(); it != end(); it++) {
			it->first->updateForce(it->second, duration);
		}
	}

	void addRegistry(RBForceGenerator* fg, DynamicRigidBody* p) {
		insert(FRPair(fg, p));
	}

	void deleteParticleRegistry(DynamicRigidBody* p) {
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

	void deleteParticleRegistry(RBForceGenerator* fg) {
		auto it = find(fg);
		//borra de la lista todas las particulas asociadas a este generador de fuerza, ademas de borrar la key en si del generador de fuerzas
		if (it != end())
			erase(fg);
	}

};


