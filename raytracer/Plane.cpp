#include "Plane.h"



Plane::Plane()
{
}


Plane::Plane(glm::vec3 V1, glm::vec3 V2, glm::vec3 V3, glm::vec3, glm::vec3 color)
{
	vertices1 = V1;
	vertices2 = V2;
	vertices3 = V3;
	col = color;
}

bool Plane::intersect(const glm::vec3 &rayorigin, const glm::vec3 &raydir, float &t0, float &t1)
{
	return false;
}

Plane::~Plane()
{
}
