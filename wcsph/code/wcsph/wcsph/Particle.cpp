#include "Particle.h"

Particle::Particle()
{
	//pos.x = 0.5f;
	//pos.y = 0.5f;
	//pos.z = 0.5f;
	pos.x = rand()%900/100.0f + 0.5f;
	pos.y = rand()%900/100.0f  + 0.5f;
	pos.z = rand()%900/100.0f  + 0.5f;
	velocity.x = 0.0f;
	velocity.y = 0.0f;
	velocity.z = 0.0f;
	acceleration.x = 0.0f;
	acceleration.y = 0.0f;
	acceleration.z = 0.0f;
	density = 1.0f;
	mass = 1.0f;
	r = rand()%100/100.0f;
	g =rand()%100/100.0f;
	b = rand()%100/100.0f;
	isSurface = false;
}

Particle::~Particle()
{

}