#include "Matrix.h"
#include "Vec4.h"
#include <math.h>


/*Vec4 Matrix::multiplication4x1(float matrix1[4][4], Vec4 vec4) {
	Vec4 matrixRes;
	for (int i = 0; i < 4; i++) {
		matrixRes.setOne(i, 0);
		for (int t = 0; t < 4; t++)
			matrixRes.setOne(i, matrixRes.getOne(i) + matrix1[i][t] * vec4.getOne(i));
	}
}

Matrix Matrix::multiplication4x4(float matrix1[4][4], float matrix2[4][4]) {
	Matrix matrixRes;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrixRes.matrix4x4[i+j] = 0;
			for (int t = 0; t < 4; t++)
				matrixRes.matrix4x4[i+j] += matrix1[i][t] * matrix2[t][j];
		}
	}
	return matrixRes;
}

Vec4 Matrix::multiplication(float translate[4][4], float scale[4][4], float rotate[4][4], Vec4 vec){
	Vec4 matrixRes;
	for (int i = 0; i < 4; i++) {
		matrixRes.setOne(i, 0);
		for (int t = 0; t < 4; t++)
			matrixRes.setOne(i, matrixRes.getOne(i) + matrix1[i][t] * vec4.getOne(i));
	}
}
*/

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


	Matrix4x4 rotate = {
		1,  0,  0,  0,
		0,  1,  0,  0,
		0,  0,  c,  -s,
		0,  0,  s,  c
	};
	multMatrixVec4(rotate, vec);

}

Vec4 scale(float size, Vec4 vec) {

}

Vec4 translate(float distant, Vec4 vec) {

}
