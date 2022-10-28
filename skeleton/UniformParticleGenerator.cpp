#include "UniformParticleGenerator.h"
#include <random>


list<Particle*> UniformParticleGenerator::generateParticles()
{
	std::random_device rd{};
	std::mt19937 gen{ rd() };

	list<Particle*> particles;

	//utilizaremos la distribucion uniforme
	uniform_real_distribution<double> dist(-1.0, 1.0);

	//como maximo creara nParticles, según la probabilidad dada
	for (int i = 0; i < _nParticles; i++) {
		int r = rand() % 100;
		if (_probability * 100 >= r) {
			//genera una particula
			_baseParticle->setColor(Vector4(1, 0.5, 0, 1));
			auto p = _baseParticle->clone();
			//siguiente valor de velocidad y posicion origen segun la distribucion gaussiana
			Vector3 newPos = Vector3(_poswidth.x * dist(gen), _poswidth.y * dist(gen), _poswidth.z* dist(gen));
			Vector3 newVel = Vector3(_velwidth.x * dist(gen), _velwidth.y * dist(gen), _velwidth.z* dist(gen));
			p->setPos(newPos+_origin); p->setVel(newVel+_velMedia); p->setAcc(Vector3(1, -10, 1)); p->setmaxLifeTime(_lifetime_media);
			particles.push_back(p);
		}
	}

	return particles;

}
