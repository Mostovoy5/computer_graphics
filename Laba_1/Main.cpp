#include <iostream>
#include <fstream>
#include "Vec3.h"
#include "Vec4.h"
#include "Sphere.cpp"
#include <vector>
#include "ObjLoader.h"
#include "Matrix.h"


void console() {
	int width = 120;
	int height = 30;
	char* screen = new char[width * height + 1];
	screen[width * height] = '\0';
	Sphere sphere(0, 2, 0, 1);
	Vec3 centerPlane(0, 0, -1);
	const int fov = 3.14f / 3.0f;
	Vec3 L = Vec3::norm(Vec3(-0.5, -0.5, -1));

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
					n = Vec3::norm(centerPlane);
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
				} else;
				screen[i + j * width] = pixel;
			};
		};
		printf(screen);
	}
	return;
}

void consolePPM() {
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
}


void triangles() {
	struct framebuffer {
		Vec3 RGB;
		float pixelDist;
		bool shadow;

		framebuffer() {
			RGB = Vec3(0, 0, 0);
			pixelDist = 9999.f;
			shadow = false;
		}
	};

	int width = 192;
	int height = 108;
	const int fov = 3.14f / 3.0f;
	Vec3 centerPlane(0, 0, -1);

	const char* path = "Obj/cow.obj";	
	ObjLoader model = ObjLoader(path);
	for (int u = 0; u < model.vertexes.size(); u++) {
		model.vertexes[(u)].vector = Vec4::getVec3(Matrix4x4::rotationZ(-1.58,model.vertexes[(u)].vector));
		model.vertexes[(u)].vector = Vec4::getVec3(Matrix4x4::rotationX(1, model.vertexes[(u)].vector));
		model.vertexes[(u)].vector = Vec4::getVec3(Matrix4x4::rotationY(1.58, model.vertexes[(u)].vector));
		model.vertexes[(u)].vector = Vec4::getVec3(Matrix4x4::translate(0,0,500 , model.vertexes[(u)].vector));
		model.vertexes[(u)].vector = Vec4::getVec3(Matrix4x4::scale(0.0025, 0.0025, 0.0025, model.vertexes[(u)].vector));
	}

	std::vector<framebuffer> fb(width * height);
	Vec3 L = Vec3::norm(Vec3(-0.75, 1, -0.75));

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			Vec2 uv = Vec2(i, j) / Vec2(width, height) * 2.0f - 1.0f;
			uv.x *= fov * 1.8;
			Vec3 origin = Vec3(-3, 0, 0);
			Vec3 dir = Vec3::norm(Vec3(1, uv.x, uv.y));
			float tes = 99999;
			Vec3 n = 0;	
			float diff = 0;

			for (int t = 0; t < model.faces.size(); t++) {
				float intersection = Vec3::triangle_intersection(origin, dir, model.vertexes[(model.faces[t].v0) - 1].vector,
																			  model.vertexes[(model.faces[t].v1) - 1].vector,
																			  model.vertexes[(model.faces[t].v2) - 1].vector);
				if (intersection > 0) {
					if (intersection < fb[i + j * width].pixelDist) {
						fb[i + j * width].pixelDist = intersection;
						Vec3 itPoint = origin + dir * intersection;
						tes = intersection;
						n = Vec3::norm(itPoint);
					}	
				}
			}
			float intersection = Vec3::planeIntersection(origin, dir, centerPlane, 1);
			if (intersection > 0) {
				if (intersection < fb[i + j * width].pixelDist) {
					fb[i + j * width].pixelDist = intersection;
					Vec3 itPoint = origin + dir * intersection;

					for (int t = 0; t < model.faces.size(); t++) {
						float shadow = Vec3::triangle_intersection(itPoint, L, model.vertexes[(model.faces[t].v0) - 1].vector,
																					   model.vertexes[(model.faces[t].v1) - 1].vector,
																				   	   model.vertexes[(model.faces[t].v2) - 1].vector);
						if (shadow > 0) {
							fb[i + j * width].shadow = true;
							break;
						}
					}

					tes = intersection;
					n = Vec3::norm(centerPlane);
				}
			}

			if (tes < 99999) {
				diff = Vec3::dot(L, n );	 
				if (diff >= 0)
					if(fb[i + j * width].shadow == true)
						fb[i + j * width].RGB = Vec3(diff/2, diff/2, diff/2);
					else
						fb[i + j * width].RGB = Vec3(diff, diff, diff);
				if (diff == 0) 
					fb[i + j * width].RGB = Vec3(0, 0, 0);
			}
			if (fb[i + j * width].pixelDist == 9999.f) {
				fb[i + j * width].RGB = Vec3(0, 0.3, 0);
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
	console();
	//consolePPM();
	//triangles();

};