#pragma once

#include <vector>
#include "Sphere.h"
#include "Plane.h"
#include "Object.h"

class World
{
public:
	// c-tors and d-tors
	World() {};
	~World();

	// public methods
	void addObject(Object* o);

	std::vector<Object*> objects;
};