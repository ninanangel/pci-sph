#include "Poly6SmoothKernel.h"

Poly6SmoothKernel::Poly6SmoothKernel(void)
{
}

Poly6SmoothKernel::~Poly6SmoothKernel(void)
{
}

vector3 Poly6SmoothKernel::getValue(vector3 *r_i, vector3 *r_j, float h_size)
{
	//r_i表示产生作用的粒子位置
	//r_j表示当前粒子位置
	vector3 temp_r(r_i->x - r_j->x, r_i->y - r_j->y, r_i->z - r_j->z);
	float r_len = temp_r.length();
	float result;
	if(r_len >= 0 && r_len <= h_size)
	{
		//result = (315/(64*PAI*h^9))*(h^2 - r^2)^3)
		result = (float)((4.921875*pow((pow(h_size, 2) - pow(r_len, 2)),3))/(PAI*pow(h_size, 9)));
	}
	else
	{
		result = 0;
	}

	temp_r = (temp_r.normalize())*result;

	return temp_r;
}

vector3 Poly6SmoothKernel::getGrads(vector3 *r_i, vector3 *r_j, float h_size)
{
	//r_i表示产生作用的粒子位置
	//r_j表示当前粒子位置
	vector3 temp_r(r_i->x - r_j->x, r_i->y - r_j->y, r_i->z - r_j->z);
	float r_len = temp_r.length();
	float result;
	if(r_len >= 0 && r_len <= h_size)
	{
		//result = (315/(64*PAI*h^9))*(-6)r*(h^2 - r^2)^2)
		result = (float)((-29.53125*r_len*(h_size*h_size - r_len*r_len)*
			(h_size*h_size - r_len*r_len))/(PAI*pow(h_size, 9)));
	}
	else
	{
		result = 0;
	}

	temp_r = (temp_r.normalize())*result;

	return temp_r;
}

vector3 Poly6SmoothKernel::getLaplacian(vector3 *r_i, vector3 *r_j, float h_size)
{
	//r_i表示产生作用的粒子位置
	//r_j表示当前粒子位置
	vector3 temp_r(r_i->x - r_j->x, r_i->y - r_j->y, r_i->z - r_j->z);
	float r_len = temp_r.length();
	float result;
	if(r_len >= 0 && r_len <= h_size)
	{
		//result = (315/(64*PAI*h^9))*(-6)*(h^2 - r^2)*(h^2 + 3*r^2))
		result = (float)((-29.53125*(h_size*h_size - r_len*r_len)*
			(h_size*h_size + 3*r_len*r_len))/(PAI*pow(h_size, 9)));
	}
	else
	{
		result = 0;
	}

	temp_r = (temp_r.normalize())*result;

	return temp_r;
}
