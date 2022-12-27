#include "FireworksGenerator.h"
#include "GravityForceGenerator.h"
#include <random>


FireworksGenerator::FireworksGenerator() : ParticleGenerator("fireworksGen", Vector3(0, 0, 0), Vector3(0, 0, 0), Vector4(0, 0, 1, 1), 0, new Particle(), 0.5)
{
	GravityForceGenerator* earth = new GravityForceGenerator({ 0,-4.5,0 });
	addForceGenerator(earth);
}

//la formula que seguiremos para crear una circunferencia con las velocidades es:
//Vector Aleatorio Normalizado * Magnitud de un vector resultante del siguiente calculo: VelocidadMedia + VarianzaVelocidad*DistribucionUniforme
//Esto nos dara particulas que irán en direcciones aleatorias, pero todas con la misma magnitud, generando una circunferencia.
//Si bloquearamos alguna de las componentes x,y o z del vector podriamos obtener circunferencias planas
list<Particle*> FireworksGenerator::generateParticles()
{
	std::random_device rd{};
	std::mt19937 gen{ rd() };
	uniform_real_distribution<double> dist(-1.0, 1.0);
	list<Particle*> fireworks;
	auto p = _lastExploded->getPayloads();
	//sacamos la varianza de la velocidad y del tiempo de vida, asi como la media asignada (está guardada en los valores de la particula base)
	Vector3 varVel = _lastExploded->getVarianzaVel(); float varLife = _lastExploded->getVarianzaLife();
	Vector3 mediaVel = _lastExploded->getVel(); float mediaLife = _lastExploded->getMaxLifeTime();
	//Conseguimos la magnitud por la que multiplicaremos un vector aleatorio para la velocidad.
	float magnitude = Vector3(mediaVel.x + varVel.x * dist(gen), mediaVel.y + varVel.y * dist(gen), mediaVel.z + varVel.z * dist(gen)).magnitude();

	//Primero, genera fireworks nuevos si tiene algún payload. Por cada payload, generará N particulas de tipo X.
	//Cada una de esas particulas tendrá el mismo valor medio y varianza de velocidad, puesto que depende del tipo.
	for (auto v : p) {
		//accede a los valores de la tupla del payload
		int nFireworks = v._Myfirst._Val;
		FireworksType t = v._Get_rest()._Myfirst._Val;
		//crea las n particulas de la carga actual con los valores calculados previamente
		//todas las particulas tendrán la misma magnitud y la posicion será la posicion en la que ha explotado la particula que esta generando esta explosion
		for (int i = 0; i < nFireworks; i++) {
			//genera una nueva particula base, diciendole el tipo de firework para que tenga los valores correspondientes
			if (!dynamic_cast<Firework*>(_baseParticle))
				return fireworks;
			Firework* f = dynamic_cast<Firework*>(_baseParticle->clone());
			f->setType(t);
			//generamos un vector aleatorio normalizado
			Vector3 randomVector = Vector3(dist(gen), dist(gen), dist(gen)).getNormalized();
			float vlife = mediaLife + varLife * dist(gen);
			f->setPos(_lastExploded->getPos()); f->setVel(randomVector*magnitude); f->setmaxLifeTime(abs(vlife));
			fireworks.push_back(f);
		}
	}

	return fireworks;

}

