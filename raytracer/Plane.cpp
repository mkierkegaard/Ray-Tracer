#include "Plane.h"
#include "Object.h"



Plane::Plane(glm::vec3 n, glm::vec3 col, glm::vec3 p) : Object (col) {
	normal = glm::normalize(n);
	point = p;
}


Plane::~Plane()
{
}
