#include "Matrix.h"
#include "Vec4.h"
#include <math.h>

Vec4 Matrix4x4::multMatrixVec4(Matrix4x4 m, Vec4 v) {
	Vec4 vRes;
	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < 4; k++)
			vRes.addOne(i, m.num[i][k] * v.getOne(k));
	}
	return vRes;
}

Matrix4x4 Matrix4x4::getMatrX(float angle) {
	float s = sin(angle);
	float c = cos(angle);

	Matrix4x4 rotate = Matrix4x4({// X 
	1.f,  0.f,  0.f,  0.f,
	0.f,  c,   -s,    0.f,
	0.f,  s,    c,    0.f,
	0.f,  0.f,  0.f,  1.f
	});
	return rotate;
};

Matrix4x4 Matrix4x4::getMatrY(float angle) {
	float s = sin(angle);
	float c = cos(angle);


	Matrix4x4 rotate = Matrix4x4({ // Y
		c,  0,  s,  0,
		0,  1,  0,  0,
	   -s,  0,  c,  0,
		0,  0,  0,  1
	});
	return rotate;
};

Matrix4x4 Matrix4x4::getMatrZ(float angle) {
	float s = sin(angle);
	float c = cos(angle);


	Matrix4x4 rotate = Matrix4x4({// Z
		c, -s,  0,  0,
		s,  c,  0,  0,
		0,  0,  1,  0,
		0,  0,  0,  1
	});
	return rotate;
};

Vec4 Matrix4x4::rotationX(float angle, Vec4 vec) {
	
	return multMatrixVec4(getMatrX(angle), vec);
}

Vec4 Matrix4x4::rotationY(float angle, Vec4 vec) {

	return multMatrixVec4(getMatrY(angle), vec);
}

Vec4 Matrix4x4::rotationZ(float angle, Vec4 vec) {

	return multMatrixVec4(getMatrZ(angle), vec);
}

Vec4 Matrix4x4::rotation(float angleX, float angleY, float angleZ, Vec4 vec) {
	return multMatrixVec4(getMatrX(angleX) * getMatrY(angleY) * getMatrZ(angleZ), vec);
}

Vec4 Matrix4x4::rotation(float angle, Vec4 vec) {
	return multMatrixVec4(getMatrX(angle) * getMatrY(angle) * getMatrZ(angle), vec);
}



Vec4 Matrix4x4::scale(float sizeX, float sizeY, float sizeZ, Vec4 vec) {
	Matrix4x4 scale = Matrix4x4({
		sizeX, 0,     0,      0,
		0,     sizeY, 0,      0,
		0,     0,     sizeZ,  0,
		0,     0,     0,      1
	});
	return multMatrixVec4(scale, vec);
}

Vec4 Matrix4x4::translate(float distantX, float distantY, float distantZ, Vec4 vec) {
	Matrix4x4 translate = Matrix4x4({// Z
	1, 0, 0, distantX,
	0, 1, 0, distantY,
	0, 0, 1, distantZ,
	0, 0, 0, 1
	});
	return multMatrixVec4(translate, vec);
}
