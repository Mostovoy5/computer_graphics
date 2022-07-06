#pragma once
#include <vector>
#include "Vec3.h"

class ObjLoader
{
public:
    struct vertex {
        float x;
        float y;
        float z;
        Vec3 vector = Vec3(x, y, z);
    };
    struct normal {
        float x;
        float y;
        float z;
        Vec3 norma = Vec3(x, y, z);
    };
    struct face {
        unsigned int v0, v1, v2;
        unsigned int n0, n1, n2;
    };

    ObjLoader(const char* path) {
        readfile(path);
    }

    std::vector<vertex> vertexes;
    std::vector<normal> normals;
    std::vector<face> faces;

    void readfile(const char* path);
};

