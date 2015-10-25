#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <glm/vec3.hpp>
#include "World.h"

#define MAX_RAY_DEPTH 5

class Ray
{
private:
	glm::vec3 origin;
	glm::vec3 direction;

public:
	Ray::Ray(World w);
	Ray::Ray(glm::vec3 orig, glm::vec3 dir);
	Ray::~Ray();
	World world;
	glm::vec3 Ray::trace(glm::vec3 &rayorgin, glm::vec3 &raydir, std::vector<Object*> &objects, const int &depth);
};

