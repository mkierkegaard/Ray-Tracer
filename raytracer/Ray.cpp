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

	glm::vec3 retcol = glm::vec3(0, 0, 0);

	if (!object) return retcol;
	
	else {
		
		// p is the point of intersection
		// lightdir is a normalized vector from p towards light source

			glm::vec3 p = rayorgin + raydir * tnear;
			glm::vec3 pn = object->getNormal(p);
			pn = glm::normalize(pn);
			glm::vec3 lightdir = glm::normalize(world.lightpos - p);
			float lightlength = glm::length(world.lightpos - p);
			glm::vec3 transmission(1.f, 1.f, 1.f);

	
			for (unsigned i = 0; i < objects.size(); i++) {
				if (objects[i]->emissionColor.x > 0) {
					for (unsigned j = 0; j < objects.size(); j++) {
						if (i != j) {
							float tnew;
							if (objects[j]->intersect(p + pn * glm::vec3(0.0000000001, 0.0000000001, 0.0000000001), lightdir, tnew, t1)) {
								if (tnew < lightlength) {
									//cout << "tnew "<<tnew<<" length: " << lightlength <<endl;
									transmission = glm::vec3(0.0, 0.0, 0.0);
									break;
								}
									
							}
						}
					}
			
					retcol += object->color * transmission * std::max(float(0), glm::dot(pn, lightdir)) * world.objects[i]->emissionColor;
				}
	
			}

		return retcol + object->emissionColor;
	}
}
