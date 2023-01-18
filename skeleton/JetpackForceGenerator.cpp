#include "JetpackForceGenerator.h"
#include <iostream>
JetpackForceGenerator::JetpackForceGenerator(float force, float fuel, float cost, bool* inputUp, std::string* text) :
	_force(force), _maxFuel(fuel), _cost(cost), isGoingUp(inputUp),  display(text) {
	_fuel = _maxFuel;
}

void JetpackForceGenerator::updateForce(Particle* particle, double t) {
	*display= "COMBUSTIBLE: " + std::to_string((int)_fuel);
	Vector3 force = { 0,0,0 }; //daremos una fuerza nula en caso de tener apenas nada de combustible;
	if(!(*isGoingUp)) { //si no esta intentando subir, recarga y además empuja hacia abajo
		recarga();
		force = { 0,-1*_force,0 };
	}
	else if(_fuel <= 0) {//si está intentando subir pero no le queda combustible, no recarga (esta intentando gastarlo)
		_fuel = 0;
		force = { 0,-1 * _force,0 };
	}
	else {
		//daremos diferente valor de fuerza según cuanta gasolina quede, cuanta menos, menos fuerza dará
		if (_fuel >= _maxFuel - (_maxFuel / 3)) { //si tiene al menos 2/3 del combustible
			force = { 0,_force,0 };
		}
		else if (_fuel >= _maxFuel * 0.333) { //si está entre 1/3 y 2/3
			force = { 0,(float)(_force * 0.6667),0 };
		}
		else if (_fuel > _maxFuel * 0.16) { //si está entre 0.5/3 y 1/3 del combustible
			force = { 0,(float)(_force * 0.4),0 };
		}
		_fuel -= _cost; //siempre que intentemos volar, gasta energia
	}
	particle->addForce(force);
	*isGoingUp = false;
}
void JetpackForceGenerator::recarga() {
	if (_fuel < _maxFuel) {
		_fuel += _cost / 2;
		if (_fuel > _maxFuel) _fuel = _maxFuel;
	}
}