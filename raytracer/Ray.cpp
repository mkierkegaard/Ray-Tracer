#include "Ray.h"
#include "Light.h"


Ray::Ray(World w)
{
	world = w;
}

Ray::Ray(glm::vec3 orig, glm::vec3 dir)
{
	Ray::origin = orig;
	direction = dir;
}

Ray::~Ray()
{
}

glm::vec3 Ray::trace(glm::vec3 &rayorgin, glm::vec3 &raydir, std::vector<Object*> &objects)
{
	float tnear = INFINITY;
	const Object* object = NULL;
	float t0, t1;

	for (unsigned i = 0; i < objects.size(); i++) {
		//float t0 = INFINITY, t1 = INFINITY;
		if (objects[i]->intersect(rayorgin, raydir, t0, t1)) {
			//if (t0 < 0) t0 = t1;
			if (t0 < tnear) {
				tnear = t0;
				object = objects[i];
			}
		}
	}

	if (!object) return glm::vec3(0, 0, 0);

	else{
		// p is the point of intersection
		// pDir is a normalized vector from p towards light source
		glm::vec3 p = rayorgin + raydir * tnear;
		glm::vec3 pdir = world.lightpos - p;
		float dist = glm::length(pdir);
		pdir = glm::normalize(pdir);

		// Look through all objects, if we find an object closer than the light source, shaded = true;
		for (auto &o : world.objects)
		if (o->intersect(p, pdir, t0, t1))
		if (t0 < dist) return glm::vec3(0.0, 0.0, 0.0);

		// Not shaded => return object's color
		return object->color;
	}
}
