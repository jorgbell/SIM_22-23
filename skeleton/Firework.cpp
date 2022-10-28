#include "Firework.h"

Firework::Firework(FireworksType t) : _type(t)
{
	Vector4 color;
	double dump;
	float mass, maxlife, groundlim;

	switch (_type)
	{
	case FIREWORK_0:
		color = ; dump = ; mass = ; maxlife = ; groundlim = ; _cargas = ;
		break;
	case FIREWORK_1:
		color = ; dump = ; mass = ; maxlife = ; groundlim = ;
		break;
	case FIREWORK_2:
		color = ; dump = ; mass = ; maxlife = ; groundlim = ;
		break;
	case FIREWORK_3:
		color = ; dump = ; mass = ; maxlife = ; groundlim = ;
		break;
	case FIREWORK_4:
		color = ; dump = ; mass = ; maxlife = ; groundlim = ;
		break;
	case FIREWORK_5:
		color = ; dump = ; mass = ; maxlife = ; groundlim = ;
		break;
	case FIREWORK_6:
		color = ; dump = ; mass = ; maxlife = ; groundlim = ;
		break;
	case FIREWORK_7:
		color = ; dump = ; mass = ; maxlife = ; groundlim = ;
		break;
	case FIREWORK_8:
		color = ; dump = ; mass = ; maxlife = ; groundlim = ;
		break;
	case FIREWORK_9:
		color = ; dump = ; mass = ; maxlife = ; groundlim = ;
		break;
	}

	setDamp(dump); setMass(mass); setColor(color); setmaxLifeTime(maxlife); setGroundLimit(groundlim);
	initRenderItem();

}

void Firework::integrate(double t)
{

}

Firework* Firework::clone() const
{
	auto f = new Firework(*this);
	f->initRenderItem();
	return f;
}
