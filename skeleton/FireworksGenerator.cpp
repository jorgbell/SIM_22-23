#include "FireworksGenerator.h"

list<Particle*> FireworksGenerator::generateParticles()
{
	return;
}

list<Firework*> FireworksGenerator::generateFireworks(vector<payload> p)
{
	list<Firework*> fireworks;
	for (auto v : p) {
		//accede a los valores de la tupla
		int nFireworks = v._Myfirst._Val;
		FireworksType t = v._Get_rest()._Myfirst._Val;

		//crea las particulas de la carga actual
		for (int i = 0; i < nFireworks; i++)
			fireworks.push_back(new Firework(t));
	}

	return fireworks;
}
