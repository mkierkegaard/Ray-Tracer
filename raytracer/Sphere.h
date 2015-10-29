#ifndef SPHERE_H
#define SPHERE_H
#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>
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
	Sphere::Sphere(glm::vec3 pos, float rad, glm::vec3 col, glm::vec3 emcolor, glm::vec3 refcolor, float trans);
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

		return true;
	}

	glm::vec3 getNormal(const glm::vec3 &p)const {

		glm::vec3 normal = glm::normalize(p - this->position);

		return normal;
	}

};

#endif