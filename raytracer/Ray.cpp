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
	const Object* light = NULL;

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
	glm::vec3 retcol = object->color;
	if (!object) return glm::vec3(0, 0, 0);
	
	else {
		// p is the point of intersection
		// pdir is a normalized vector from p towards light source
		//If != lightsource
		if (object->emissionColor.length() == 0)
		{
			glm::vec3 p = rayorgin + raydir * tnear;
			glm::vec3 pdir = world.lightpos - p;
			float dist = glm::length(pdir);
			pdir = glm::normalize(pdir);

			// Look through all objects, if we find an object closer than the light source, shaded = true;
			for (auto &o : world.objects)
				if (o->intersect(p, pdir, t0, t1))
					if (t0 < dist) return glm::vec3(0.0, 0.0, 0.0);

			for (int i = 0; i < world.objects.size(); i++) {
				glm::vec3 transmission(1.f, 1.f, 1.f);
				if (world.objects[i]->emissionColor.length() > 0) {
					glm::vec3 lightdir = glm::normalize(world.lightpos - p);
					for (int j = 0; j < world.objects.size(); j++) {
						if (i != j) {
							if (world.objects[j]->intersect(p + pdir * glm::vec3(_FBIAS, _FBIAS, _FBIAS), lightdir, t0, t1)) {
								transmission = glm::vec3(0.f, 0.f, 0.f);
								break;
							}
						}
					}
					retcol += object->color * transmission * std::max(float(0), glm::dot(pdir, lightdir)) * world.objects[i]->emissionColor;
				}
			}
		}

		// Not shaded => return object's color
		return retcol + object->emissionColor;
	}
}
