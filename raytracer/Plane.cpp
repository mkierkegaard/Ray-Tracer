#include "Plane.h"
#include "Object.h"



Plane::Plane(glm::vec3 n, glm::vec3 c, glm::vec3 p) {
	normal = glm::normalize(n);
	color = c;
	point = p;
}


Plane::~Plane()
{
}
