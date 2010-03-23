#include "SpikySmoothKernel.h"

SpikySmoothKernel::SpikySmoothKernel(void)
{
}

SpikySmoothKernel::~SpikySmoothKernel(void)
{
}

vector3 SpikySmoothKernel::getValue(vector3 *r_i, vector3 *r_j, float h_size)
{
	//r_i表示产生作用的粒子位置
	//r_j表示当前粒子位置
	vector3 temp_r(r_i->x - r_j->x, r_i->y - r_j->y, r_i->z - r_j->z);
	float r_len = temp_r.length();
	float result;
	if(r_len >= 0 && r_len <= h_size)
	{
		//result = (15*(h - r)^3/(PAI*h^6))
		result = (float)(15*(h_size - r_len)*(h_size - r_len)*(h_size - r_len)/(PAI*pow(h_size, 6)));
	}
	else
	{
		result = 0;
	}

	temp_r = (temp_r.normalize())*result;

	return temp_r;
}

vector3 SpikySmoothKernel::getGrads(vector3 *r_i, vector3 *r_j, float h_size)
{
	//r_i表示产生作用的粒子位置
	//r_j表示当前粒子位置
	vector3 temp_r(r_i->x - r_j->x, r_i->y - r_j->y, r_i->z - r_j->z);
	float r_len = temp_r.length();
	float result;
	if(r_len >= 0 && r_len <= h_size)
	{
		//result = (-15*3*(h - r))/(PAI*h^6))
		result = (float)(-45*(h_size - r_len)/(PAI*pow(h_size, 6)));
	}
	else
	{
		result = 0;
	}

	temp_r = (temp_r.normalize())*result;

	return temp_r;
}

vector3 SpikySmoothKernel::getLaplacian(vector3 *r_i, vector3 *r_j, float h_size)
{
	//r_i表示产生作用的粒子位置
	//r_j表示当前粒子位置
	vector3 temp_r(r_i->x - r_j->x, r_i->y - r_j->y, r_i->z - r_j->z);
	float r_len = temp_r.length();
	float result;
	if(r_len >= 0 && r_len <= h_size)
	{
		//result = (45/(PAI*h^6))
		result = (float)(45/(PAI*pow(h_size, 6)));
	}
	else
	{
		result = 0;
	}

	temp_r = (temp_r.normalize())*result;

	return temp_r;
}
