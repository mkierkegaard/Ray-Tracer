#include "Sphere.h"
#include "Object.h"

Sphere::Sphere(glm::vec3 pos, float rad, glm::vec3 col) : Object (col)
{
	position = pos;
	radius = rad;
}

Sphere::~Sphere()
{

}

bool Sphere::intersect(const glm::vec3 &rayorigin, const glm::vec3 &raydir, float &t0, float &t1) const{

	glm::vec3 l = this->position - rayorigin;	
	float tca = glm::dot(l, raydir);
	if (tca < 0) return false;
	float d2 = glm::dot(l, l) - tca * tca;
	if (d2 > (this->radius*this->radius)) return false;
	float thc = sqrt((this->radius*this->radius) - d2);
	t0 = tca - thc;
	t1 = tca + thc;

	return true;
}