#pragma once
#include "mtxlib.h"
#include "math.h"
#define PAI    3.1415926

/**
本类处理Smoothing Kernel的计算
此类为超类，具体实现在子类中
*/
class SmoothKernel
{
public:
	SmoothKernel(void);
	virtual ~SmoothKernel(void);

public:
	virtual vector3 getValue(vector3 *r_i, vector3 *r_j, float h_size)=0;
	virtual vector3 getGrads(vector3 *r_i, vector3 *r_j, float h_size)=0;
	virtual vector3 getLaplacian(vector3 *r_i, vector3 *r_j, float h_size)=0;
};
