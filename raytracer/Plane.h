#ifndef PLANE_H
#define PLANE_H

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include "Object.h"

class Plane : public Object
{
public:
	Plane(glm::vec3 n, glm::vec3 p, glm::vec3 color, glm::vec3 emcol, glm::vec3 refcol, float trans);
	glm::vec3 normal, point;
	~Plane();

	bool intersect(const glm::vec3 &rayorigin, const glm::vec3 &raydir, float &t0, float &t1) {

	glm::vec3 n = -normal;

		if (glm::dot(raydir, n) >= 0.0001)
		{
			t0 = glm::dot((point - rayorigin), n) / glm::dot(raydir, n);
			return (t0 >= 0.0);
		}

		return false;
	}

	glm::vec3 getNormal(const glm::vec3 &p)const {

		return this->normal;
	}
};

#endif
