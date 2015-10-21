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

	void World::addObject(Object& o);

};