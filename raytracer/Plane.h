#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>

class Plane
{
public:
	Plane();
	Plane(glm::vec3 V1, glm::vec3 V2, glm::vec3 V3, glm::vec3, glm::vec3 color);
	bool Plane::intersect(const glm::vec3 &rayorigin, const glm::vec3 &raydir, float &t0, float &t1);
	glm::vec3 vertices1, vertices2, vertices3, col;
	~Plane();
};

