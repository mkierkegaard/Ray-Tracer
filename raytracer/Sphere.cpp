#include "Sphere.h"
#include "Object.h"

Sphere::Sphere(glm::vec3 pos, float rad, glm::vec3 col, glm::vec3 emcolor, glm::vec3 refcolor, float trans) : Object(pos, col, emcolor, refcolor, trans)
{
	position = pos;
	radius = rad;

}

Sphere::~Sphere()
{

}