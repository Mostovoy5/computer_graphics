#pragma once
#include "Vec4.h"
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
	static Vec4 rotation(float angle, Vec4 vec);
	static Vec4 scale(float size, Vec4 vec);
	static Vec4 translate(float distant, Vec4 vec);


};

