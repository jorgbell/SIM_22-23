#include "GaussianParticleGenerator.h"
#include <random>


list<Particle*> GaussianParticleGenerator::generateParticles()
{
	std::random_device rd{};
	std::mt19937 gen{ rd() };

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
			auto p = _baseParticle->clone();
			//siguiente valor de velocidad y posicion origen segun la distribucion gaussiana
			Vector3 newpos = Vector3(posXDist(gen), posYDist(gen), posZDist(gen));
			Vector3 newVel = Vector3(velXDist(gen), velYDist(gen), velZDist(gen));
			p->init(newpos, newVel, Vector3(1, -10, 1), Vector4(0.5, 1, 0.5, 1), 0.99, _lifetime_media);
			particles.push_back(p);
		}
	}

	return particles;
}
