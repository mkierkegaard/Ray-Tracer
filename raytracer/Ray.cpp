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

float mix(const float &a, const float &b, const float &mix)
{
	return b * mix + a * (1 - mix);
}

float brdf(glm::vec3 in, glm::vec3 out, glm::vec3 normal) {

	float brdf;
	brdf = std::max(float(0), glm::dot(normal, out));
	
	return brdf;
}

glm::vec3 calcOffset() {

	//bad random generator? should use modern method?
	float u = (float)rand() / RAND_MAX;
	float v = (float)rand() / RAND_MAX;

	//evenly distributed
	float theta = 2 * M_PI*u;
	float cosphi = 2 * v - 1;
	float phi = acos(cosphi);

	float x = 0.5 * cos(theta) * sin(phi);
	float y = 0.5 * sin(theta) * sin(phi);
	float z = 0.5 * cosphi;

	glm::vec3 offset = glm::vec3(x, y, z);

	return offset;
}

glm::vec3 Ray::trace(glm::vec3 &rayorgin, glm::vec3 &raydir, std::vector<Object*> &objects, const int &depth)
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

	// p is the point of intersection
	// lightdir is a normalized vector from p towards light source

	glm::vec3 p = rayorgin + raydir * tnear;
	glm::vec3 pn = object->getNormal(p);
	pn = glm::normalize(pn);

	glm::vec3 offset1 = calcOffset();
	glm::vec3 offset2 = calcOffset();

	world.lightpos1 += offset1;
	world.lightpos2 += offset2;

	glm::vec3 lightdir1 = glm::normalize(world.lightpos1 - p);
	glm::vec3 lightdir2 = glm::normalize(world.lightpos2 - p);
	glm::vec3 transmission1 = glm::vec3(1.0, 1.0, 1.0);
	glm::vec3 transmission2 = glm::vec3(1.0, 1.0, 1.0);
		
			for (unsigned i = 0; i < objects.size(); i++) {
				if (objects[i]->emissionColor.x > 0) {
				transmission1 = glm::vec3(1.0, 1.0, 1.0);
				transmission2 = glm::vec3(1.0, 1.0, 1.0);
				for (unsigned j = 0; j < objects.size(); j++) {
					if (objects[j]->emissionColor.x == 0) {
						if (objects[j]->intersect(p, lightdir1, t0, t1)) {
							if (t0 < length(world.lightpos1 - p))
							{
								transmission1 = glm::vec3(0.0, 0.0, 0.0);
							}
						}
						if (objects[j]->intersect(p, lightdir2, t0, t1)) {

							if (t0 < length(world.lightpos2 - p))
							{
								transmission2 = glm::vec3(0.0, 0.0, 0.0);
							}

						}
					}
				}
					if (glm::length(object->reflectanceColor) > 0 && depth < MAX_RAY_DEPTH) {

						float facingratio = glm::dot(-p, pn);
						float fresneleffect = mix(pow(1 - facingratio, 3), 1, 0.1);
						glm::vec3 refldir = glm::normalize(raydir - pn * glm::vec3(2, 2, 2) * glm::dot(raydir, pn));
						glm::vec3 reflection = trace(p + pn, refldir, objects, depth + 1);

						retcol += object->reflectanceColor*reflection* transmission1 * brdf(raydir, lightdir1, pn) * world.objects[i]->emissionColor;
						retcol += object->reflectanceColor*reflection *transmission2 * brdf(raydir, lightdir2, pn) * world.objects[i]->emissionColor;
					}
					
				retcol +=  object->color * transmission1 * brdf(raydir, lightdir1, pn) * world.objects[i]->emissionColor;
				retcol +=  object->color * transmission2 * brdf(raydir, lightdir2, pn) * world.objects[i]->emissionColor;

				}
			}
			//indirect light
			float absorbtion = 0.5;
			if (depth < 3 && absorbtion < static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) {
				int numrays = 2;
				for (int i = 0; i < numrays; i++) {
					float randx = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 2 - 1;
					float randy = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 2 - 1;
					float randz = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 2 - 1;

					glm::vec3 randdir(randx, randy, randz);
					randdir = glm::normalize(randdir);
					Ray ray(world);
					glm::vec3 tracedcol = ray.trace(p, randdir, objects, depth + 1);
					float pdf = 1 / (2 * M_PI);
					float randbrdf = brdf(raydir, randdir, pn);
					float newRayCos = std::max(0.0f, glm::dot(object->getNormal(p), randdir));
					
					if (glm::length(tracedcol) > 0)
						retcol += randbrdf* newRayCos*glm::vec3(tracedcol.x / (1 - absorbtion) * pdf, tracedcol.y / (1 - absorbtion)*pdf, tracedcol.z / (1 - absorbtion) *pdf);
				}
			}

		return retcol + object->emissionColor;
	}
