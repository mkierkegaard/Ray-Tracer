#include "Plane.h"
#include "Object.h"



Plane::Plane(glm::vec3 n, glm::vec3 col, glm::vec3 p, glm::vec3 emcol) : Object (col, emcol)
{
	normal = n;
	point = p;
}


Plane::~Plane()
{
}
