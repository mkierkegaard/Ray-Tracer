#pragma once

#include <vector>
#include "Sphere.h"
#include "Plane.h"
#include "Object.h"

class World
{
public:
	// c-tors and d-tors
	World();
	~World();

	// public methods

	std::vector<Object*> objects;

	//std::vector<Light*> lights;

	void World::addObject(Object& o);

	glm::vec3 lightpos = glm::vec3(0, 4, -2);

	//void World::addLight(Light& l);
};