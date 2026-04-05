#pragma once
#include <vector>

class Mesh {
public:
    Mesh();
    ~Mesh();

private:

    std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> texCoords;
	std::vector<unsigned int> indices;
};
