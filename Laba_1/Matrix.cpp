#include "Matrix.h"
#include "Vec4.h"
#include <math.h>
	
Matrix4x4 multMatrix(Matrix4x4 m1, Matrix4x4 m2) {
	Matrix4x4 m3;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++)
				m3.num[i][j] += m1.num[i][k] * m2.num[k][j];
		}
	}
	return m3;
}

Vec4 multMatrixVec4(Matrix4x4 m, Vec4 v) {
	Vec4 vRes;
	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < 4; k++)
			vRes.addOne(i, m.num[i][k] * v.getOne(i));
	}
	return vRes;
}


Vec4 rotationX(float angle, Vec4 vec) {
	float s = sin(angle);
	float c = cos(angle);


	Matrix4x4 rotate = {// X 
		1,  0,  0,  0,
		0,  c, -s,  0,
		0,  s,  c,  0,
		0,  0,  0,  1
	};
	multMatrixVec4(rotate, vec);
}

Vec4 rotationY(float angle, Vec4 vec) {
	float s = sin(angle);
	float c = cos(angle);


	Matrix4x4 rotate = { // Y
		c,  0,  s,  0,
		0,  1,  0,  0,
	   -s,  0,  c,  0,
	    0,  0,  0,  1
	};
	multMatrixVec4(rotate, vec);
}

Vec4 rotationZ(float angle, Vec4 vec) {
	float s = sin(angle);
	float c = cos(angle);


	Matrix4x4 rotate = {// Z
		c, -s,  0,  0,
		s,  c,  0,  0,
		0,  0,  1,  0,
		0,  0,  0,  1
	};
	multMatrixVec4(rotate, vec);
}

Vec4 scale(float sizeX, float sizeY, float sizeZ, Vec4 vec) {
	Matrix4x4 scale = {
		sizeX, 0,     0,      0,
		0,     sizeY, 0,      0,
		0,     0,     sizeZ,  0,
		0,     0,     0,      1
	};
	multMatrixVec4(scale, vec);
}

Vec4 translate(float distantX, float distantY, float distantZ, Vec4 vec) {
	Matrix4x4 translate = {// Z
	1, 0, 0, distantX,
	0, 1, 0, distantY,
	0, 0, 1, distantZ,
	0, 0, 0, 1
	};
	multMatrixVec4(translate, vec);
}
