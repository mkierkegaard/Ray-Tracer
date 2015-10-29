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

	if ((glm::length(object->reflectanceColor) > 0.f || object->transparancy > 0.f) && depth < MAX_RAY_DEPTH) {
		
		float facingratio = glm::dot(-raydir, pn);
		glm::vec3 fresneleffect(mix(pow(1.f - facingratio, 3.f), 1.f, 0.1f), mix(pow(1.f - facingratio, 3.f), 1.f, 0.1f), mix(pow(1.f - facingratio, 3.f), 1.f, 0.1f));
		glm::vec3 refldir = glm::normalize(raydir - pn * glm::vec3(2.f, 2.f, 2.f) * glm::dot(raydir, pn));
		glm::vec3 reflection = trace(p, refldir, objects, depth + 1);
		glm::vec3 refraction(0.0f, 0.0f, 0.0f);

		if (object->transparancy > 0.f) {
			glm::vec3 incident = raydir;
			float n1, n2;
			n1 = 1.0f;
			n2 = 1.4f;
			float r = n1 / n2;
		
			float cosTheta1 = glm::dot(raydir, -pn);
			float cosTheta2 = sqrt(1.f - r*r*(1.f - cosTheta1*cosTheta1));

			glm::vec3 refractiondir = (r*raydir + (float)(r*cosTheta1 - cosTheta2)*pn);

			glm::vec3 pOut = p + (refractiondir * 2.f * glm::dot(refractiondir, object->point - p));
			glm::vec3 normOut = object->getNormal(pOut);

			r = n2 / n1;

			float cosTheta1out = glm::dot(refractiondir, -normOut);
			float cosTheta2out = sqrt(1.f - r*r*(1.f - cosTheta1out*cosTheta1out));

			glm::vec3 refrdirOut = glm::normalize((r*raydir + (r*cosTheta1out - cosTheta2out)*normOut));
			
			float R0 = pow((n1 - n2) / (n1 + n2), 2);
			float refCof = R0 + (1.f - R0)* pow(1.f - cosTheta1, 5);
			
			refraction = trace(pOut, refrdirOut, objects, depth + 1);

			if ((float)rand() / RAND_MAX  < refCof ) {
				
				retcol += refraction;
				
			}		
			else {
				
				//cout << (reflection* object->reflectanceColor * brdf(p, lightdir1, pn)).x << endl;
				retcol += (reflection* object->reflectanceColor * brdf(p, lightdir1, pn));
				retcol += (reflection* object->reflectanceColor * brdf(p, lightdir2, pn));
			}
		}
		else {

			retcol += (reflection* object->reflectanceColor * brdf(p, lightdir1, pn));
			retcol += (reflection* object->reflectanceColor * brdf(p, lightdir2, pn));
		}
		//cout << "refraction : " << refraction.x << endl;
		
		
		
		

		//retcol += (refraction* object->transparancy + object->reflectanceColor * reflection )* object->color;
		//retcol += (refraction* object->transparancy + object->reflectanceColor * reflection )* object->color;
	}

	else {
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
			}
			retcol += object->color * transmission1 * brdf(raydir, lightdir1, pn) * world.objects[i]->emissionColor;
			retcol += object->color * transmission2 * brdf(raydir, lightdir2, pn) * world.objects[i]->emissionColor;
		}
	}
	//indirect light
	float absorbtion = 0.5;
	
	if (depth < 3 && absorbtion < static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) {
		int numrays = 10;
		for (int i = 0; i < numrays; i++) {

			float u = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float v = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

			float x = cos(2 * M_PI * u);
			float y = sin(2 * M_PI * u);
			float z = v;

			glm::vec3 randdir(x, y, z);

			glm::vec3 sw = pn;
			glm::vec3 su = glm::normalize(glm::cross((glm::abs(sw.x) > 0.1 ? glm::vec3(0, 1, 0) : glm::vec3(1, 0, 0)), sw));
			glm::vec3 sv = glm::cross(sw, su);

			glm::mat3 rot = glm::mat3(sv, sw, su);

			randdir = glm::normalize(randdir) * rot;
			//Ray ray(world);
			glm::vec3 tracedcol = trace(p, randdir, objects, depth + 1);
			float pdf = 1 / (2 * M_PI);
			float randbrdf = brdf(raydir, randdir, pn);
			//float newRayCos = std::max(0.0f, glm::dot(object->getNormal(p), randdir));

			if (glm::length(tracedcol) > 0)
				retcol += randbrdf *(1.f/absorbtion)* pdf* tracedcol;
		}
	}

	return retcol + object->emissionColor;
}
