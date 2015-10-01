#include "Sphere.h"



Sphere::Sphere()
{

}

Sphere::Sphere(glm::vec3 pos, float rad, glm::vec3 col)
{
	Sphere::position = pos;
	radius = rad;
	color = col;
}

Sphere::~Sphere()
{

}
