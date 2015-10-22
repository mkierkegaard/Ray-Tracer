#ifndef LIGHT_H
#define LIGHT_H
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#pragma once

class Light

{
public:
	Light(glm::vec3 p, glm::vec3 c);
	~Light();
	glm::vec3 position, color;
};

#endif