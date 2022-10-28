#include "FireworksGenerator.h"
#include <random>


FireworksGenerator::FireworksGenerator(int nParticles) : ParticleGenerator("fireworksGen", Vector3(0,0,0), Vector3(0,0,0), nParticles, new Particle())
{
	
}

list<Particle*> FireworksGenerator::generateParticles()
{
	//TODO: Este metodo tendrá todo. Las particulas normales realmente serán fireworks de tipo 0.
	//genera nParticles particulas base que funcionaran como explosion
	//posibilidad de extender este metodo según el tipo de firework que haya explotado, para cambiar el color, la forma de la explosino, etc
	//será una distribucion uniforme en las tres direcciones, esta distribucion acabara generando una esfera
	//se observara mejor segun lo grande que sea el nParticles
	
	std::random_device rd{};
	std::mt19937 gen{ rd() };
	uniform_real_distribution<double> dist(-1.0, 1.0);


	list<Firework*> fireworks;
	//Primero, genera fireworks nuevos si tiene algún payload
	for (auto v : p) {
		//accede a los valores de la tupla del payload
		int nFireworks = v._Myfirst._Val;
		FireworksType t = v._Get_rest()._Myfirst._Val;

		//crea las particulas de la carga actual
		//TODO Dar los valores necesarios al Firework
		for (int i = 0; i < nFireworks; i++) {
			Firework* f = new Firework(t);
			//pillamos las varianzas para el calculo de la distribucion
			Vector3 varVel = f->getVarianzaVel();
			float varLife = f->getVarianzaLife();
			//



			fireworks.push_back(f);


		}
	}
	//despues, genera el resto de particulas

	return fireworks;

}

