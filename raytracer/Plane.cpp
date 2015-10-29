#include "Plane.h"
#include "Object.h"



Plane::Plane(glm::vec3 n, glm::vec3 col, glm::vec3 p, glm::vec3 emcol, glm::vec3 refcol, float trans) : Object (p, col, emcol, refcol, trans)
{
	normal = n;
	point = p;
}


Plane::~Plane()
{
}
