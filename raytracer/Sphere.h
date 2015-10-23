#ifndef SPHERE_H
#define SPHERE_H

#include <stdlib.h>
#include <stdio.h>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include "Object.h"

class Sphere : public Object
{
private:
	

protected:
	

public:
	Sphere::Sphere(glm::vec3 pos, float rad, glm::vec3 col, glm::vec3 emcolor);
	Sphere::~Sphere();
	float radius;
	glm::vec3 position;

	bool intersect(const glm::vec3 &rayorigin, const glm::vec3 &raydir, float &t0, float &t1) {

		glm::vec3 l = this->position - rayorigin;
		float tca = glm::dot(l, raydir);
		if (tca < 0) return false;
		float d2 = glm::dot(l, l) - tca * tca;
		if (d2 > (this->radius*this->radius)) return false;
		float thc = sqrt((this->radius*this->radius) - d2);
		t0 = tca +- thc;
		//t1 = tca + thc;

		//cout << "Intersects with sphere" << endl;

		return true;
	}

};

#endif