#pragma once
#include "Particle.h"
class Projectile_Pistol : public Particle
{
public:
	/*
		Constructor predeterminado para la pistola, con los valores fijos seg�n el enunciado.
		No se da la posibilidad de crear un proyectil de pistola de otra manera porque en ese caso es m�s logico crear directamente una part�cula con valores personalizados.
		como siempre tendra una velocidad de 35 m/s, damos la posibilidad de dar una direcci�n personalizada para definir hacia donde
		debe moverse el proyectil
	*/
	Projectile_Pistol(Vector3 p, Vector3 dir, Vector4 c)
	{
		if (!dir.isNormalized())	
			dir.normalize();
		init(p, dir * 35.f, Vector3(0.0, -1.0, 0.0),c,0.99f, 2.0);
	};
	~Projectile_Pistol() {};

};

