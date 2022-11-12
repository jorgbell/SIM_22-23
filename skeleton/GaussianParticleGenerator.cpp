#include "GaussianParticleGenerator.h"
#include <random>
#include <chrono>


list<Particle*> GaussianParticleGenerator::generateParticles()
{
	std::random_device rd{};
	std::mt19937 FuenteGaussiana{ rd() };

	list<Particle*> particles;
	//utilizaremos una distribucion gaussiana para cada uno de los componentes de velocidad y posicion origen.
	normal_distribution<double> velXDist(_velMedia.x, std_dev_vel.x);
	normal_distribution<double> velYDist(_velMedia.y, std_dev_vel.y);
	normal_distribution<double> velZDist(_velMedia.z, std_dev_vel.z);

	normal_distribution<double> posXDist(_origin.x, std_dev_pos.x);
	normal_distribution<double> posYDist(_origin.y, std_dev_pos.y);
	normal_distribution<double> posZDist(_origin.z, std_dev_pos.z);

	//como maximo creara nParticles, según la probabilidad dada
	for (int i = 0; i < _nParticles; i++) {
		int r = rand() % 100;
		if (_probability * 100 >= r) {
			//genera una particula
			_baseParticle->setColor(Vector4(0.5, 0, 1, 1));
			auto p = _baseParticle->clone();
			//siguiente valor de velocidad y posicion origen segun la distribucion gaussiana
			Vector3 newpos = Vector3(posXDist(FuenteGaussiana), posYDist(FuenteGaussiana), posZDist(FuenteGaussiana));
			Vector3 newVel = Vector3(velXDist(FuenteGaussiana), velYDist(FuenteGaussiana), velZDist(FuenteGaussiana));
			p->setVel(newVel); p->setPos(newpos); p->setAcc(Vector3(0,0,0));p->setmaxLifeTime(_lifetime_media);
			particles.push_back(p);
		}
	}

	return particles;
}
