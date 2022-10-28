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
	FIREWORK_7,
	FIREWORK_8,
	FIREWORK_9,
};

using payload = std::tuple<int, FireworksType>;
class Firework : public Particle
{
public:
	Firework(FireworksType t);

	virtual void integrate(double t);
	virtual Firework* clone() const;
	FireworksType getFireworkType() { return _type; }

private:
	//vector de cargas. indica cuantos Fireworks crear de cada tipo. 
	//Puede haber varias cargas y así crear varios tipos de Fireworks con un solo unico Firework origen.
	std::vector<payload> _cargas;
	//tipo de Firework. El tipo de Firework indicará también qué vector de cargas tendrá el siguiente en el árbol.
	FireworksType _type;

};

