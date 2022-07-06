#pragma once
#include "Vec4.h"
#include "Matrix.cpp"
class Matrix4x4
{
public:
	float num[4][4];
	
	Matrix4x4() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				num[i][j] = 0;
			}
		}
	}
	Matrix4x4(float a[16]) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				num[i][j] = a[i];
			}
		}
	}

	Matrix4x4(float a[4][4]) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				num[i][j] = a[i][j];
			}
		}
	}

	Matrix4x4(float a1, float a2, float a3, float a4, 
			  float a5, float a6, float a7, float a8, 
			  float a9, float a10, float a11, float a12, 
			  float a13, float a14, float a15, float a16) {
				num[0][0] = a1;
				num[0][0] = a2;
				num[0][0] = a3;
				num[0][0] = a4;
				num[0][0] = a5;
				num[0][0] = a6;
				num[0][0] = a7;
				num[0][0] = a8;
				num[0][0] = a9;
				num[0][0] = a10;
				num[0][0] = a11;
				num[0][0] = a12;
				num[0][0] = a13;
				num[0][0] = a14;
				num[0][0] = a15;
				num[0][0] = a16;

		
	}

	/*static Matrix multiplication4x4(float matrix1[4][4], float matrix2[4][4]);
	static Vec4 multiplication(float translate[4][4], float scale[4][4], float rotate[4][4], Vec4 vec);*/
	static Matrix4x4 multMatrix(Matrix4x4 m1, Matrix4x4 m2);
	static Vec4 multMatrixVec4(Matrix4x4 m, Vec4 v);

	static Vec4 rotationX(float angle, Vec4 vec);
	static Vec4 rotationY(float angle, Vec4 vec);
	static Vec4 rotationZ(float angle, Vec4 vec);
	static Vec4 rotation(float angleX, float angleY, float angleZ, Vec4 vec);

	static Vec4 scale(float sizeX, float sizeY, float sizeZ, Vec4 vec);
	static Vec4 translate(float distantX, float distantY, float distantZ, Vec4 vec);


};

