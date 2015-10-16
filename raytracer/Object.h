#ifndef OBJECT_H
#define OBJECT_H

#pragma once
#include <glm/vec3.hpp>
#include <glm/glm.hpp>

class Object
{
public:

	Object();
	Object(glm::vec3 color);
	virtual ~Object() {};
	glm::vec3 color;

protected:

};

#endif