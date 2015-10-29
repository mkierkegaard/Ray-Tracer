#ifndef OBJECT_H
#define OBJECT_H

#pragma once
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <iostream>

using namespace std;

class Object
{
public:

	Object();
	Object(glm::vec3 point, glm::vec3 color, glm::vec3 emcolor, glm::vec3 refcolor, float trans);
	glm::vec3 color;
	glm::vec3 emissionColor;
	glm::vec3 reflectanceColor;
	glm::vec3 point;
	float transparancy;
	virtual bool intersect(const glm::vec3 &rayorigin, const glm::vec3 &raydir, float &t0, float &t1) = 0;
	virtual glm::vec3 getNormal(const glm::vec3 &p) const = 0;
protected:

};

#endif