/**
* Copyright (c) 2001,SJTU
* All rights reserved.
*
* @file Particle.h
* @date 2009/07/01
* @author SJTU_SPH_group
*/

#ifndef FLUID_H
#define FLUID_H

#include<Vector>
#include"Particle.h"
#include "mtxlib.h"
#include "SmoothKernel.h"
#include "Poly6SmoothKernel.h"
#include "SpikySmoothKernel.h"
#include "ViscositySmoothKernel.h"

#define CELL_SIZE 10	//划分的cell数量为10*10*10
#define INIT_NUM 500	//初始的粒子数量
#define MIN_DENSITY 0.01 //定义最小的密度
/**
* @brief 粒子系统
**/
class Fluid{
public:
	std::vector<Particle*> particles;								//所有粒子
	int neighbors[INIT_NUM][INIT_NUM];								//All the neighbors information,NEED TO UPDATE IN THE FUTURE
	std::vector<Particle*> cell[CELL_SIZE][CELL_SIZE][CELL_SIZE];		//记录每个cell的粒子
	float worldSize;												//场景大小							
	float particleSize;												//绘制的粒子大小
	float jumpFactor;												//碰到墙壁反弹的系数
	float viscosityFactor;											//粘滞系数
	float pressureFactor;											//压强系数
	float densityRest;												//剩余密度的调整参数
	float surfaceFactor;											//表面张力系数
	float surfaceThreshold;											//表面点阈值
	float viscosity_h;												//粘滞力作用范围
	float pressure_h;												//压强作用范围
	float surface_h;												//表面张力作用范围
	float density_h;												//计算密度范围
	float k_value;                                                  //The value of k when computing pressure
	float s_density;														//The standard density value

	SmoothKernel* skp;											//表示smoothkernel的指针
	Poly6SmoothKernel* pskp;
	SpikySmoothKernel* sskp;
	ViscositySmoothKernel* vskp;

	Fluid();
	~Fluid();
	
	void init();		//初始化
	void render(int t);		//渲染
	void updateDensity();
	void updateCell();
	void initNeighbors();   //找到所有点的周围粒子
	void caculateNextFrame(int t);
	void addParticles(std::vector<Particle*> newParticles);

	vector3 getPressure(Particle * particle);
	vector3 getViscosity(Particle * particle);
	vector3 getSurface(Particle * particle);
	vector3 getExternalForce();

};

#endif