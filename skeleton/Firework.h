#pragma once
#include "Particle.h"
#include <tuple>
#include <vector>

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
	Firework(FireworksType t);

	virtual void integrate(double t);
	virtual Firework* clone() const;
	FireworksType getFireworkType() { return _type; }
	std::vector<payload> getPayloads() { return _cargas; }
	float getMinAge() { return _minAge; }
	float getMaxAge() { return _maxAge; }
	Vector3 getMinVel() { return _minVelocity; }
	Vector3 getMaxVel() { return _maxVelocity; }

	Vector3 getVarianzaVel() {
		return Vector3(
			_maxVelocity.x - _minVelocity.x,
			_maxVelocity.y - _minVelocity.y,
			_maxVelocity.z - _minVelocity.z);
	}
	float getVarianzaLife() { return _maxAge - _minAge; }

private:
	//vector de cargas. indica cuantos Fireworks crear de cada tipo. 
	//Puede haber varias cargas y así crear varios tipos de Fireworks con un solo unico Firework origen.
	std::vector<payload> _cargas;
	//tipo de Firework. El tipo de Firework indicará también qué vector de cargas tendrá el siguiente en el árbol.
	FireworksType _type;
	Vector3 _minVelocity, _maxVelocity;
	float _minAge, _maxAge;

};

