#include "ViscositySmoothKernel.h"

ViscositySmoothKernel::ViscositySmoothKernel(void)
{
}

ViscositySmoothKernel::~ViscositySmoothKernel(void)
{
}

vector3 ViscositySmoothKernel::getValue(vector3 *r_i, vector3 *r_j, float h_size)
{
	//r_i表示产生作用的粒子位置
	//r_j表示当前粒子位置
	vector3 temp_r(r_i->x - r_j->x, r_i->y - r_j->y, r_i->z - r_j->z);
	float r_len = temp_r.length();
	float result;
	if(r_len >= 0 && r_len <= h_size)
	{
		//result = (15*(-r^3/(2*h^3) + r^2/h^2 + h/2r - 1)/(2*PAI*h^3))
		result = (float)(7.5*(- pow(r_len, 3)/(2*pow(h_size, 3)) 
			+ r_len*r_len/(h_size*h_size) + h_size/(2*r_len) - 1)/(PAI*pow(h_size, 3)));
	}
	else
	{
		result = 0;
	}

	temp_r = (temp_r.normalize())*result;

	return temp_r;
}

vector3 ViscositySmoothKernel::getGrads(vector3 *r_i, vector3 *r_j, float h_size)
{
	//r_i表示产生作用的粒子位置
	//r_j表示当前粒子位置
	vector3 temp_r(r_i->x - r_j->x, r_i->y - r_j->y, r_i->z - r_j->z);
	float r_len = temp_r.length();
	float result;
	if(r_len >= 0 && r_len <= h_size)
	{
		//result = (15*(-3*r^2/(2*h^3) + 2*r/h^2 - h/(2*r^2))/(2*PAI*h^3))
		result = (float)(7.5*(-3*r_len*r_len/(2*pow(h_size, 3)) + 2*r_len/(h_size*h_size)
			- h_size/(2*r_len*r_len))/(PAI*pow(h_size, 3)));
	}
	else
	{
		result = 0;
	}

	temp_r = (temp_r.normalize())*result;

	return temp_r;
}

vector3 ViscositySmoothKernel::getLaplacian(vector3 *r_i, vector3 *r_j, float h_size)
{
	//r_i表示产生作用的粒子位置
	//r_j表示当前粒子位置
	vector3 temp_r(r_i->x - r_j->x, r_i->y - r_j->y, r_i->z - r_j->z);
	float r_len = temp_r.length();
	float result;
	if(r_len >= 0 && r_len <= h_size)
	{
		//result = (45*(h-r)/(PAI*h^6))
		result = (float)(45*(h_size - r_len)/(PAI*pow(h_size, 6)));
	}
	else
	{
		result = 0;
	}

	temp_r = (temp_r.normalize())*result;

	return temp_r;
}
