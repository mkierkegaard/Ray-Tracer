#include <stdlib.h>
#include <stdio.h>
#include <glm/vec3.hpp>

class Ray
{
private:
	glm::vec3 origin;
	glm::vec3 direction;

public:
	Ray::Ray();
	Ray::Ray(glm::vec3 orig, glm::vec3 dir);
	Ray::~Ray();
};

