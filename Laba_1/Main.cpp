#include <iostream>
#include <fstream>
#include "Vec3.h"
#include "Sphere.cpp"
#include <vector>
#include "ObjLoader.h"
#include "Matrix.h"


void console() {
	int width = 1920;
	int height = 1080;	
	Sphere sphere(0, 2, 0, 1);
	Vec3 centerPlane(0, 0, -1);	
	const int fov = 3.14f / 3.0f;
	std::vector<Vec3> framebuffer(width * height);
	Vec3 L = Vec3::norm(Vec3(-0.5, -0.5, -1));

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			Vec2 uv = Vec2(i, j) / Vec2(width, height) * 2.0f - 1.0f;
			uv.x *= fov * 1.8;
			Vec3 origin = Vec3(-2, 0, 0);
			Vec3 dir = Vec3::norm(Vec3(1, uv.x, uv.y));
			float diff = 0;

			for (int k = 0; k < 5; k++) {
				float tes = 99999;
				//framebuffer[i + j * width] = Vec3(0.f, 0.f, 0.f);

				Vec3 n = 0;
				Vec2 intersection = Vec3::sphereIntersectionPlus(origin - sphere.giveCenter(),
					dir, sphere.giveRadius());
				if (intersection.x > 0) {
					Vec3 itPoint = origin - sphere.giveCenter() + dir * intersection.x;
					tes = intersection.x;
					n = Vec3::norm(itPoint);
				}
				intersection = Vec3::planeIntersection(origin, dir, centerPlane, 1);
				if (intersection.x > 0 && intersection.x < tes) {
					tes = intersection.x;
					n = Vec3::norm(centerPlane);
				}
				if (tes < 99999) {
					diff = Vec3::dot(n, L);
					framebuffer[i + j * width] = Vec3(diff, diff, diff);
				}
				else break;
			}
		};
	};

	std::ofstream ofs;
	ofs.open("./out.ppm");
	ofs << "P3\n" << width << " " << height << "\n255\n";

	for (size_t i = 0; i < height * width; i++) {
		int c1 = (int)(255.0f * Vec3::clamp(framebuffer[i].x, 0.f, 1.0f));
		int c2 = (int)(255.0f * Vec3::clamp(framebuffer[i].y, 0.f, 1.0f));
		int c3 = (int)(255.0f * Vec3::clamp(framebuffer[i].z, 0.f, 1.0f));
		ofs << c1 << " " << c2 << " " << c3 << std::endl;
	}
	ofs.close();
/*
	width = 120;
	height = 30;
	char* screen = new char[width * height + 1];
	screen[width * height] = '\0';

	for (int t = 0; t < 100000; t++) {
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				Vec2 uv = Vec2(i, j) / Vec2(width, height) * 2.0f - 1.0f;
				uv.x *= fov*1.8;
				Vec3 origin = Vec3(-2, 0, 0);
				Vec3 dir = Vec3::norm(Vec3(1, uv.x, uv.y));
				origin = Vec3::rotateY(origin, 0.25);
				dir = Vec3::rotateY(dir, 0.25);
				origin = Vec3::rotateZ(origin, t * 0.005);
				dir = Vec3::rotateZ(dir, t * 0.005);
				char pixel = ' ';
				float diff = 0;
				//if (Vec3::sphereIntersection(origin, dir, centerSphere, radiusSphere)) pixel = '#';
				
				float tes = 99999;
					
				Vec3 n = 0;
				Vec2 intersection = Vec3::sphereIntersectionPlus(origin - sphere.giveCenter(),
																	 dir, sphere.giveRadius());
				if (intersection.x > 0) {
					Vec3 itPoint = origin - sphere.giveCenter() + dir * intersection.x;
					tes = intersection.x;
					n = Vec3::norm(itPoint);
				}
				intersection = Vec3::planeIntersection(origin, dir, centerPlane, 1);
				if (intersection.x > 0 && intersection.x < tes) {
					tes = intersection.x;
					n = centerPlane;
				}
				if (tes < 99999) {
					diff = Vec3::dot(n, L);
					if (diff < 0) {
						pixel = '.';
					}
					else if (diff >= 0 && diff < 0.2) {
						pixel = 'o';
					}
					else if (diff >= 0.2 && diff < 0.5) {
						pixel = '*';
					}
					else if (diff >= 0.5 && diff < 0.8) {
						pixel = 'O';
					}
					else if (diff >= 0.8) {
						pixel = '#';						
					}
				}
				else break;
				screen[i + j * width] = pixel;
			};
		};
		printf(screen);
	}*/
	return;
}

void triangles() {
	struct framebuffer {
		Vec3 RGB;
		float pixelDist;

		framebuffer() {
			RGB = Vec3(0, 0, 0);
			pixelDist = 9999.f;
		}
	};

	int width = 1920;
	int height = 1080;
	const int fov = 3.14f / 3.0f;

	const char* path = "Obj/cow.obj";	
	ObjLoader modelCow = ObjLoader(path);

	std::vector<framebuffer> fb(width * height);
	Vec3 L = Vec3::norm(Vec3(-5000, -5000, -5000));

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			Vec2 uv = Vec2(i, j) / Vec2(width, height) * 2.0f - 1.0f;
			uv.x *= fov * 1.8;
			Vec3 origin = Vec3(-1000, 0, 0);
			Vec3 dir = Vec3::norm(Vec3(1, uv.x, uv.y));
			float diff = 0;

			for (int u = 0; u < modelCow.vertexes.size(); u++) {

				Vec4 vectemp = modelCow.vertexes[u].vector;
				
				modelCow.vertexes[u].vector = Matrix4x4::multiplication4x4(
					Matrix4x4::multiplication4x4(translate, scale), rotate);
			}

			for (int t = 0; t < modelCow.faces.size(); t++) {
				float tes = 99999;
				Vec3 n = 0;
				float intersection = Vec3::triangle_intersection(origin, dir, modelCow.vertexes[(modelCow.faces[t].v0) - 1].vector,
																			  modelCow.vertexes[(modelCow.faces[t].v1) - 1].vector,
																			  modelCow.vertexes[(modelCow.faces[t].v2) - 1].vector);
				if (intersection > 0) {
					if (intersection < fb[i + j * width].pixelDist) {
						fb[i + j * width].pixelDist = intersection;
						Vec3 itPoint = origin + dir * intersection;
						tes = intersection;
						n = Vec3::norm(itPoint);
					}
					if (tes < 99999) {
						diff = Vec3::dot(n, L);
						if (diff > 0) {
							fb[i + j * width].RGB = Vec3(diff, diff, diff);
						}if (diff <= 0) {
							fb[i + j * width].RGB = Vec3(0, 0, 0);
						}
					}
				}
				if (intersection >= 0) {
					fb[i + j * width].RGB = Vec3(0, 1, 0);
				}

			}
		}
	}
	std::ofstream ofs;
	ofs.open("./cow.ppm");
	ofs << "P3\n" << width << " " << height << "\n255\n";

	for (size_t i = 0; i < height * width; i++) {
		int c1 = (int)(255.0f * Vec3::clamp(fb[i].RGB.x, 0.f, 1.0f));
		int c2 = (int)(255.0f * Vec3::clamp(fb[i].RGB.y, 0.f, 1.0f));
		int c3 = (int)(255.0f * Vec3::clamp(fb[i].RGB.z, 0.f, 1.0f));
		ofs << c1 << " " << c2 << " " << c3 << std::endl;
	}
	ofs.close();
}

int main() {
	//console();
	triangles();

};