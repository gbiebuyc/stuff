#ifndef CUBE_HPP
#define CUBE_HPP

#include <iostream>
#include <Shader.hpp>
#include <array>
using namespace std;

class Cube {
public:
	static void init();
	static void setViewMat(float *mat);
	static void draw(float *mat, array<float, 3> color);

private:
	static GLuint VAO, VBO, EBO;
	static Shader *shader;
	static float viewMat[16];
};

#endif
