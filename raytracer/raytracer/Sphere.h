#pragma once
#include <glm/vec3.hpp>

glm::vec3 position;
float radius;
glm::vec3 color;

class Sphere
{
public:
	Sphere();
	Sphere(glm::vec3 pos, float rad, glm::vec3 col);
	~Sphere();
};

