#pragma once
#include "Particle.h"
#include <tuple>
#include <vector>
#include <cmath>

enum FireworksType {
	FIREWORK_0,
	FIREWORK_1,
	FIREWORK_2,
	FIREWORK_3,
	FIREWORK_4,
	FIREWORK_5,
	FIREWORK_6,
	FIREWORK_7
};

using payload = std::tuple<int, FireworksType>;
class Firework : public Particle
{
public:
	Firework(Vector3 initPos = Vector3(0,0,0), Vector3 initVel = Vector3(1,1,1), FireworksType t = FIREWORK_5);

	virtual Firework* clone() const;
	void setType(FireworksType t);
	FireworksType getFireworkType() { return _type; }
	std::vector<payload> getPayloads() { return _cargas; }
	Vector3 getMinVel() { return _minVelocity; }
	Vector3 getMaxVel() { return _maxVelocity; }

	Vector3 getVarianzaVel() {
		return Vector3(
			std::pow(_maxVelocity.x - _minVelocity.x,2),
			std::pow(_maxVelocity.y - _minVelocity.y, 2),
			std::pow(_maxVelocity.z - _minVelocity.z, 2));
	}
	float getVarianzaLife() { return std::pow(_maxAge - _minAge,2); }

private:
	//vector de cargas. indica cuantos Fireworks crear de cada tipo. 
	//Puede haber varias cargas y así crear varios tipos de Fireworks con un solo unico Firework origen.
	std::vector<payload> _cargas;
	//tipo de Firework. El tipo de Firework indicará también qué vector de cargas tendrá el siguiente en el árbol.
	FireworksType _type;
	Vector3 _minVelocity, _maxVelocity;
	float _minAge, _maxAge;

};

