#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include "World.h"
#include <cmath>


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

