#include"Fluid.h"
#include <stdlib.h>
#include <olectl.h>														// OLE控制库头文件
#include <math.h>														// 数学函数头文件
#include <gl\gl.h>	
#include <gl\glu.h>	
#include <GL/glut.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

Fluid::Fluid()
{
	init();
	worldSize = 10.0f;
	particleSize = 0.1f;
	jumpFactor = 0.0f;
	viscosityFactor = 0.005f;
	pressureFactor = 0.05f;
	densityRest = 0.0f;
	surfaceFactor = 0.5f;
	surfaceThreshold = 0.1f;
	viscosity_h = 1.0f;
	pressure_h = 1.0f;
	surface_h = 0.1f;
	density_h = 1.0f;
	k_value = 0.01f;
	s_density = 1000f;

	//初始化smoothkernel的指针
	skp = 0;
	pskp = new Poly6SmoothKernel();
	sskp = new SpikySmoothKernel();
	vskp = new ViscositySmoothKernel();
	//	//使用时将具体指针赋给基类指针
	//eg:
	//	skp = pskp;
	//	skp->getGrads();
}

Fluid::~Fluid()
{

}
void Fluid::init()
{
	particles.clear();
	for(int i = 0;i<INIT_NUM;i++){
		Particle * p = new Particle();
		particles.push_back(p);
		int cellx = (int)(p->pos.x*CELL_SIZE/worldSize);
		int celly = (int)(p->pos.y*CELL_SIZE/worldSize);
		int cellz = (int)(p->pos.z*CELL_SIZE/worldSize);
		cell[cellx][celly][cellz].push_back(p);
	}

}
void Fluid::addParticles(std::vector<Particle*> newParticles)
{
	
}

void Fluid::initNeighbors()
{
	int count;
	for(int i=0; i<particles.size(); i++)
	{
		count = 0;
		for(int j=0; j<particles.size(); j++)
		{
			if(j == i) continue;
			if((particles[j]->pos - particles[i]->pos).length() < pressure_h)
			{
				neighbors[i][++count] = j;
			}
		}
		neighbors[i][0] = count;		//the counter of the neighbors of i
	}
}

void Fluid::caculateNextFrame(int t)
{

	//updateCell();
	//updateDensity();
	//find all the neighbors information
	initNeighbors();
	
	vector3 temp_density;
	for(int i=0; i<particles.size(); i++)
	{
		//compute density information
		skp = pskp;
		temp_density.set(0.0f, 0.0f, 0.0f);
		for(int j=0; j<neighbors[i][0]; j++)
		{
			if(j == i)
			{
				continue;
			}
			temp_density  = temp_density + particles[neighbors[i][j+1]]->mass*skp->getValue(&(particles[i]->pos),
				&(particles[neighbors[i][j+1]]->pos), density_h);
		}
		particles[i]->density = temp_density.length();

		//compute pressure pi(t)
		//particles[i]->pressure = (k_value*s_density/7)*(pow(particles[i]->density/s_density, 7) - 1);
		particles[i]->pressure = 1119*(pow(particles[i]->density/s_density, 7) - 1);
	}

	for(int i=0; i<particles.size(); i++)
	{
		//compute forces p
		//compute forces v
		//compute forces g
		//compute forces ext
	}

/*	for(int i = 0;i<particles.size();i++){
		
		vector3 force = getPressure(particles[i]) + getViscosity(particles[i])+getSurface(particles[i])+getExternalForce();
		particles[i]->acceleration.x = force.x/particles[i]->mass;
		particles[i]->acceleration.y = force.y/particles[i]->mass;
		particles[i]->acceleration.z = force.z/particles[i]->mass;
		
		//Here we should use a leap-frog scheme
		particles[i]->velocity.x += particles[i]->acceleration.x*t/1000.0f;
		particles[i]->velocity.y += particles[i]->acceleration.y*t/1000.0f;
		particles[i]->velocity.z += particles[i]->acceleration.z*t/1000.0f;
		float newx = particles[i]->pos.x + particles[i]->velocity.x*t/1000.0f;
		float newy = particles[i]->pos.y + particles[i]->velocity.y*t/1000.0f;
		float newz = particles[i]->pos.z + particles[i]->velocity.z*t/1000.0f;
		if(newx<0||newx>=worldSize){
			particles[i]->velocity.x*=-jumpFactor;
		}else{
			particles[i]->pos.x = newx;
		}
		if(newy<0||newy>=worldSize){
			particles[i]->velocity.y*=-jumpFactor;
		}else{
			particles[i]->pos.y = newy;
		}
		if(newz<0||newz>=worldSize){
			particles[i]->velocity.z*=-jumpFactor;
		}else{
			particles[i]->pos.z = newz;
		}
	}*/

	
}
void Fluid::render(int t)
{
	for(int i = 0;i<particles.size();i++){
		glColor3f(particles[i]->r,particles[i]->g, particles[i]->b);
		glPushMatrix();
		glTranslatef(particles[i]->pos.x,particles[i]->pos.y,particles[i]->pos.z);
		glutSolidSphere(0.25,9,9);
		glPopMatrix();
	}
	caculateNextFrame(t);
}

void Fluid::updateDensity(){
	vector3 temp_density; 
	skp = pskp;
	for(int i=0; i<particles.size(); i++)
	{
		temp_density.set(0.0f, 0.0f, 0.0f);
		for(int j=0; j<particles.size(); j++)
		{
			if(j == i)
			{
				continue;
			}
			temp_density  = temp_density + particles[j]->mass*skp->getValue(&(particles[i]->pos),
				&(particles[j]->pos), density_h);
		}
		particles[i]->density = temp_density.length();
	}
}

/*void Fluid::updateCell(){
	for(int i = 0;i<CELL_SIZE;i++){
		for(int j = 0;j<CELL_SIZE;j++){
			for(int k = 0;k<CELL_SIZE;k++){
				cell[i][j][k].clear();
			}
		}
	}
	for(int i = 0;i<particles.size();i++){
		int cellx = (int)(particles[i]->pos.x*CELL_SIZE/worldSize);
		int celly = (int)(particles[i]->pos.y*CELL_SIZE/worldSize);
		int cellz = (int)(particles[i]->pos.z*CELL_SIZE/worldSize);
		cell[cellx][celly][cellz].push_back(particles[i]);
	}
}*/
vector3 Fluid::getPressure(Particle * particle)
{
	//vector3 v(0.0f,0.0f,0.0f);
	////////////////test///////////////////////////////////////
	//skp = pskp;
	//vector3 ri(1.0f, 1.0f, 1.0f);//////////产生作用的粒子 
	//vector3 rj(2.0f, 2.0f, 2.0f);//////////当前粒子
	//float h_size = 100;
	//v = skp->getGrads(&ri, &rj, h_size);
	//////////////////////////////////////////////////////////	
	vector3 v(0.0f, 0.0f, 0.0f);
	vector3 temp_result;
	float p_i, p_j;
	float temp_density;
	Particle* temp_particle = 0;
	skp = sskp;
	//遍历所有粒子计算压力之和
	for(int i=0; i<particles.size(); i++)
	{
		temp_particle = particles[i];
		if((temp_particle->pos - particle->pos).length() > pressure_h)
		{
			continue;
		}
		p_i = pressureFactor*(particle->density - densityRest);
		p_j = pressureFactor*(temp_particle->density - densityRest);
		temp_density = temp_particle->density;
		if(temp_density < MIN_DENSITY)
		{
			temp_density = MIN_DENSITY;
		}
		temp_result = (temp_particle->mass)*(((p_i + p_j)/(2*temp_density))*
			skp->getGrads(&(temp_particle->pos), &(particle->pos), pressure_h));
		v = v + temp_result;
	}
	return v;
}
vector3 Fluid::getViscosity(Particle * particle)
{
	vector3 v(0.0f,0.0f,0.0f);
	vector3 temp_result;
	Particle* temp_particle = 0;
	float temp_density;
	skp = vskp;
	//遍历所有粒子计算压力之和
	for(int i=0; i<particles.size(); i++)
	{
		temp_particle = particles[i];
		//temp_result.set(0.0f, 0.0f, 0.0f);
		if((temp_particle->pos - particle->pos).length() > viscosity_h)
		{
			continue;
		}
		temp_density = temp_particle->density;
		if(temp_density < MIN_DENSITY)
		{
			temp_density = MIN_DENSITY;
		}
		temp_result = (viscosityFactor*(temp_particle->mass)*
			(((temp_particle->velocity - particle->velocity).length())/(temp_density)))*
			(skp->getLaplacian(&(temp_particle->pos), &(particle->pos), viscosity_h)).length()*
			(temp_particle->velocity - particle->velocity).normalize();
			//(particle->velocity - temp_particle->velocity).normalize();
		v = v + temp_result;
	}
	return v;
}
vector3 Fluid::getSurface(Particle * particle)
{
	vector3 v(0.0f,0.0f,0.0f);
	
	return v;
}
vector3 Fluid::getExternalForce()
{
	vector3 v(0.0f,-9.81f,0.0f);
	
	return v;
}