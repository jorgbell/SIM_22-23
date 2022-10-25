#include "UniformParticleGenerator.h"
#include <random>


list<Particle*> UniformParticleGenerator::generateParticles()
{
	std::random_device rd{};
	std::mt19937 gen{ rd() };

	list<Particle*> particles;

	//utilizaremos la distribucion uniforme
	uniform_real_distribution<double> dist(-1.0, 1.0);

	//como maximo creara nParticles, seg�n la probabilidad dada
	for (int i = 0; i < _nParticles; i++) {
		int r = rand() % 100;
		if (_probability * 100 >= r) {
			//genera una particula
			auto p = _baseParticle->clone();
			//siguiente valor de velocidad y posicion origen segun la distribucion gaussiana
			Vector3 newpos = Vector3(dist(gen), dist(gen), dist(gen));
			Vector3 newVel = Vector3(dist(gen), dist(gen), dist(gen));
			p->setVel(newVel); p->setPos(newpos); p->setAcc(Vector3(1, -10, 1)); p->setColor(Vector4(1, 1, 0.5, 1)); p->setmaxLifeTime(_lifetime_media);
			particles.push_back(p);
		}
	}

	return particles;





}
