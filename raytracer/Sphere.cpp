#include "Sphere.h"
#include "Object.h"

Sphere::Sphere(glm::vec3 pos, float rad, glm::vec3 col) : Object(col)
{
	position = pos;
	radius = rad;
	cout << "skapar en sfär" << endl;
}

Sphere::~Sphere()
{

}
