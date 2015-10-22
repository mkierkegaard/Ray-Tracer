#include "World.h"
#include "Object.h"
#include "Light.h"

World::World() {}

World::~World() {}

void World::addObject(Object& o)
{
	objects.push_back(&o);
}

/*void World::addLight(Light& l)
{
	lights.push_back(&l);
}*/