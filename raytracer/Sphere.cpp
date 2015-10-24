#include "Sphere.h"
#include "Object.h"

Sphere::Sphere(glm::vec3 pos, float rad, glm::vec3 col, glm::vec3 emcolor, glm::vec3 refcolor) : Object(col, emcolor, refcolor)
{
	position = pos;
	radius = rad;
}

Sphere::~Sphere()
{

}
