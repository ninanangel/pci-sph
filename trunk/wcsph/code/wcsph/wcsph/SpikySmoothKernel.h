#pragma once
#include "smoothkernel.h"

class SpikySmoothKernel :
	public SmoothKernel
{
public:
	SpikySmoothKernel(void);
	~SpikySmoothKernel(void);

public:
	vector3 getValue(vector3 *r_i, vector3 *r_j, float h_size);
	vector3 getGrads(vector3 *r_i, vector3 *r_j, float h_size);
	vector3 getLaplacian(vector3 *r_i, vector3 *r_j, float h_size);
};
