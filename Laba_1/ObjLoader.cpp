#include "ObjLoader.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


void ObjLoader::readfile(const char* path)
{
    std::stringstream s;
    std::ifstream fin;
    fin.open(path);
    std::string line = "";
    std::string prefix = "";
    int i = 0;

    if (!fin)
        return;
    while (std::getline(fin, line))
    {
        s.clear();
        s.str(line);
        s >> prefix;

        if (prefix == "v") {
            vertex v;
            s >> v.x >> v.y >> v.z;
            v.vector = Vec3(v.x, v.y, v.z);
            this->vertexes.push_back(v);
        }
        if (prefix == "vn") {
            normal n;
            s >> n.x >> n.y >> n.z;
            n.norma = (n.x, n.y, n.z);
            this->normals.push_back(n);
        }
        if (prefix == "f") {
            char ignore;
            face f;
            s >> f.v0 >> ignore >> f.n0 >> f.v1 >> ignore >> f.n1 >> f.v2 >> ignore >> f.n2;
            faces.push_back(f);
        }
    }
}
