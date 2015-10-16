#include "World.h"
#include "Object.h"

World::~World()
{

}

void World::addObject(Object* o)
{
	objects.push_back(o);
}