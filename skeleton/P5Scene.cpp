#include "P5Scene.h"

P5Scene::P5Scene(PxPhysics* gPhys, PxScene* gSc, PxMaterial* gMat, Camera* cam, std::stack<Scene*> sceneManager) :
	Scene(gPhys, gSc, gMat, cam, sceneManager, "Practica_5")
{
	ground = new RenderItem(CreateShape(physx::PxBoxGeometry(100.0, 0.5, 100.0)), &boxt, Vector4(0.5, 0.5, 0.5, 1));
	RegisterRenderItem(ground);
	sys = new ParticleSystem();

	base = new Particle();
	FuenteWind = new UniformParticleGenerator("FuenteWind", boxt.p, Vector3(0, 10, 0), { 0,1,0,1 }, 3, base, { 30,0.1,30 }, { 3,0.1,3 }, 0.6, 30);
	FuenteWhirlWind = new UniformParticleGenerator("FuenteWhirlWind", boxt.p, Vector3(0, 2, 0), { 1,0,0,1 }, 3, base, { 50,10,50 }, { 3,3,3 }, 2, 10);
	FuenteExplosion = new UniformParticleGenerator("FuenteExplosion", boxt.p, Vector3(0, 20, 0), { 0,0,1,1 }, 1, base, { 30,0.1,30 }, { 3,0.1,3 }, 0.6, 10);
	earthGravity = new GravityForceGenerator(Vector3(0, -9.8, 0));
	moonGravity = new GravityForceGenerator(Vector3(0, -1.62, 0));
	smokeGravity = new GravityForceGenerator(Vector3(0, -0.50, 0));
	Vector3 windRegion = { boxt.p.x, boxt.p.y + 45, boxt.p.z };
	Vector3 whirlwindRegion = { boxt.p.x + 20, boxt.p.y, boxt.p.z - 10 };

	wind = new WindForceGenerator({ 2,2,10 }, windRegion, 40, { 0,1,0,0 }, 1, 0.01);
	whirlwind = new WhirlwindForceGenerator(whirlwindRegion, 100, { 1,0,0,0 }, 0.6);
	FuenteWind->addForceGenerator(smokeGravity);
	FuenteWind->addForceGenerator(wind);

	explosion = new ExplosionForceGenerator(windRegion, { 0,0,1,0 }, 100, 50, 2, &exploded);


	FuenteWhirlWind->addForceGenerator(earthGravity);
	FuenteWhirlWind->addForceGenerator(whirlwind);

	FuenteExplosion->addForceGenerator(explosion);
	FuenteExplosion->addForceGenerator(moonGravity);
	exploded = false;

}

void P5Scene::Init()
{


}

void P5Scene::Release()
{
	delete sys;
	delete FuenteWind;
	delete FuenteWhirlWind;
	delete base;
	delete ground;
	delete earthGravity;
	delete moonGravity;
	delete wind;
	delete whirlwind;
	delete explosion;
}

void P5Scene::update(double t)
{
	sys->update(t);
	if (exploded)
		exploded = false;
}

void P5Scene::keyPress(unsigned char key)
{
	switch (toupper(key))
	{
	case 'P':
		if (sys->getNumGenerators() > 0) {//si hay alguno en pantalla, no puede añadirlo. Si el que esta en pantalla es el mismo, se desactiva con este boton
			if (sys->getParticleGenerator("FuenteWind")) {
				sys->erase("FuenteWind");
			}
		}
		else {
			sys->addParticleGenerator(FuenteWind);
		}
		break;
	case 'O':
		if (sys->getNumGenerators() > 0) {//si hay alguno en pantalla, no puede añadirlo. Si el que esta en pantalla es el mismo, se desactiva con este boton
			if (sys->getParticleGenerator("FuenteWhirlWind")) {
				sys->erase("FuenteWhirlWind");
			}
		}
		else {
			sys->addParticleGenerator(FuenteWhirlWind);
		}
		break;

	case 'I':
		if (sys->getNumGenerators() > 0) {//si hay alguno en pantalla, no puede añadirlo. Si el que esta en pantalla es el mismo, se desactiva con este boton
			if (sys->getParticleGenerator("FuenteExplosion")) {
				sys->erase("FuenteExplosion");
			}
		}
		else {
			sys->addParticleGenerator(FuenteExplosion);
		}
		break;
	case 'E':
		exploded = !exploded;
		break;
	default:
		break;
	}
}
