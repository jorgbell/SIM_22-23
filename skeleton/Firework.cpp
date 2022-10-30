#include "Firework.h"

Firework::Firework(Vector3 initPos, Vector3 initVel, FireworksType t) : Particle(initPos, initVel), _type(t)
{
	//valores de una particula generica
	Vector4 color = Vector4(1, 1, 0, 1);
	double dump = 0.999f;
	float mass = 1.0f; float groundlim = -1;
	setType(t);
	setDamp(dump); setMass(mass); setColor(color); setGroundLimit(groundlim);
}


Firework* Firework::clone() const
{
	auto f = new Firework(*this);
	f->initRenderItem();
	return f;
}

void Firework::setType(FireworksType t)
{
	_type = t;
	//valores para calcular las medias de la particula Firework
	switch (_type)
	{
	case FIREWORK_0:
		_cargas = {}; _minVelocity = { -1,-2,-1 };
		_maxVelocity = { 1,5,1 }; _minAge = 0; _maxAge = 2;
		break;
	case FIREWORK_1:
		_cargas.push_back({ 5, FIREWORK_0 });
		_minVelocity = { -3,0,-3 }; _maxVelocity = { 3,0,3 }; _minAge = 1; _maxAge = 3;
		break;
	case FIREWORK_2:
		_cargas.push_back({ 5, FIREWORK_1 }); _cargas.push_back({ 3, FIREWORK_0 });
		_minVelocity = { -7,0,-10 }; _maxVelocity = { 7,5,10 }; _minAge = 2; _maxAge = 4;
		break;
	case FIREWORK_3:
		_cargas.push_back({ 5,FIREWORK_2 }); _cargas.push_back({ 3,FIREWORK_1 }); _cargas.push_back({ 2,FIREWORK_0 });
		_minVelocity = { -5,-2,-5 }; _maxVelocity = { 5,3,5 }; _minAge = 3; _maxAge = 4;
		break;
	case FIREWORK_4:
		_cargas.push_back({ 5,FIREWORK_2 }); _cargas.push_back({ 3,FIREWORK_1 }); _cargas.push_back({ 2,FIREWORK_0 }); _cargas.push_back({ 3,FIREWORK_0 });
		_minVelocity = { -5,3,0 }; _maxVelocity = { 5,5,0 }; _minAge = 0; _maxAge = 0;
		break;
	case FIREWORK_5:
		_cargas.push_back({ 5,FIREWORK_0 }); _cargas.push_back({ 3,FIREWORK_1 }); _cargas.push_back({ 2,FIREWORK_2 }); _cargas.push_back({ 3,FIREWORK_1 }); _cargas.push_back({ 5,FIREWORK_4 });
		_minVelocity = { -10,-1,0 }; _maxVelocity = { 10,4,0 }; _minAge = 0; _maxAge = 1;
		break;
	case FIREWORK_6:
		_cargas.push_back({ 5,FIREWORK_0 });
		_minVelocity = { -3,-0.5,0 }; _maxVelocity = { 3,0.25,0 }; _minAge = 0.5; _maxAge = 1.5;
		break;
	case FIREWORK_7:
		_cargas.push_back({ 25,FIREWORK_6 });
		_minVelocity = { -5,-0.5,0 }; _maxVelocity = { 5,0,0 }; _minAge = 4; _maxAge = 6;
		break;
	}

	Vector3 velMedia = Vector3(
		(_maxVelocity.x + _minVelocity.x) / 2,
		(_maxVelocity.y + _minVelocity.y) / 2,
		(_maxVelocity.z + _minVelocity.z) / 2);

	float lifeMedia = (_maxAge + _minAge) / 2;
	setVel(velMedia); setmaxLifeTime(lifeMedia);
}
