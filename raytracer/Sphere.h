#include <stdlib.h>
#include <stdio.h>
#include <glm/vec3.hpp>

class Sphere
{
private:
	glm::vec3 position;
	float radius;
	glm::vec3 color;

public:
	Sphere::Sphere();
	Sphere::Sphere(glm::vec3 pos, float rad, glm::vec3 col);
	Sphere::~Sphere();
};

