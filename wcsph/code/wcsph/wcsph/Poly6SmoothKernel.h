#pragma once
#include "smoothkernel.h"

/**
This class deals with the calculation of 
*/
class Poly6SmoothKernel :
	public SmoothKernel
{
public:
	Poly6SmoothKernel(void);
	~Poly6SmoothKernel(void);	

public:
	vector3 getValue(vector3 *r_i, vector3 *r_j, float h_size);
	vector3 getGrads(vector3 *r_i, vector3 *r_j, float h_size);
	vector3 getLaplacian(vector3 *r_i, vector3 *r_j, float h_size);
};
