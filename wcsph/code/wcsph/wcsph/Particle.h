/**
* Copyright (c) 2001,SJTU
* All rights reserved.
*
* @file Particle.h
* @date 2009/07/01
* @author SJTU_SPH_group
*/

#ifndef PARTICLE_H
#define PARTICLE_H
#include "mtxlib.h"

/**
* @brief 流体的粒子
**/
class Particle{
public:
	vector3 pos;			//粒子位置
	vector3 velocity;		//粒子速度
	vector3 acceleration;	//粒子加速度
	float density;			//粒子密度
	float pressure;			//The pressure of the particle
	float mass;				//粒子质量
	float r,g,b;			//粒子颜色
	bool isSurface;			//粒子是否是边界点

	Particle();
	
	~Particle();

};



#endif