#include "Sphere.h"
#include "Object.h"

Sphere::Sphere(glm::vec3 pos, float rad, glm::vec3 col, glm::vec3 emcolor) : Object(col, emcolor)
{
	position = pos;
	radius = rad;
	cout << "skapar en sfär" << endl;
}

Sphere::~Sphere()
{

}
