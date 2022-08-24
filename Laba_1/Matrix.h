#pragma once
#include "Vec4.h"

class Matrix4x4
{
public:
	float num[4][4];
	
	Matrix4x4() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				num[i][j] = 0.f;
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
				num[0][1] = a2;
				num[0][2] = a3;
				num[0][3] = a4;
				num[1][0] = a5;
				num[1][1] = a6;
				num[1][2] = a7;
				num[1][3] = a8;
				num[2][0] = a9;
				num[2][1] = a10;
				num[2][2] = a11;
				num[2][3] = a12;
				num[3][0] = a13;
				num[3][1] = a14;
				num[3][2] = a15;
				num[3][3] = a16;

		
	}

	Matrix4x4 operator*(Matrix4x4 const& m2) {
		Matrix4x4 m3;
		for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++)
				m3.num[i][j] += num[i][k] * m2.num[k][j];
			}
		}
		return m3;
	};

	static Vec4 multMatrixVec4(Matrix4x4 m, Vec4 v);

	static Matrix4x4 getMatrX(float angle);
	static Matrix4x4 getMatrY(float angle);
	static Matrix4x4 getMatrZ(float angle);

	static Vec4 rotationX(float angle, Vec4 vec);
	static Vec4 rotationY(float angle, Vec4 vec);
	static Vec4 rotationZ(float angle, Vec4 vec);
	static Vec4 rotation(float angleX, float angleY, float angleZ, Vec4 vec);
	static Vec4 rotation(float angle, Vec4 vec);


	static Vec4 scale(float sizeX, float sizeY, float sizeZ, Vec4 vec);
	static Vec4 translate(float distantX, float distantY, float distantZ, Vec4 vec);


};

