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
	
	//cout << objects.size();
	glm::vec3 retcol = glm::vec3(0,0,0);
	if (!object) {
		//cout << "!object";
		return glm::vec3(0, 0, 0);
	}
	else {
		// p is the point of intersection
		// pdir is a normalized vector from p towards light source
		//If != lightsource
		//return object->color;

		float emissioncolorLength = (object->emissionColor.x + object->emissionColor.y + object->emissionColor.z) / 3;

		glm::vec3 lightpos = glm::vec3(0.0, 4, -2);
		
		if (emissioncolorLength == 0)
		{
			glm::vec3 p = rayorgin + raydir * tnear;
			glm::vec3 pdir = lightpos - p;
			glm::vec3 pn = object->getNormal(p);
			float dist = glm::length(pdir);
			pdir = glm::normalize(pdir);
			
			// Look through all objects, if we find an object closer than the light source, shaded = true;
	
			for (int i = 0; i < objects.size(); i++) {
				glm::vec3 transmission(1.f, 1.f, 1.f);
				float emissioncolorLengthI = (objects[i]->emissionColor.x + objects[i]->emissionColor.y + objects[i]->emissionColor.z) / 3;
				//cout << "col x: " << world.objects[i]->emissionColor.x << endl;
				if (emissioncolorLengthI > 0) {
					//cout << "emissioncolorLengthI : " << emissioncolorLengthI <<  endl;
					
					glm::vec3 lightdir = glm::normalize(lightpos - p);
					for (int j = 0; j < objects.size(); j++) {
						if (i != j) {
							float tnew = t0;
							if (objects[j]->intersect(p + glm::vec3(pn.x* 0.0001,pn.y*0.00001 ,pn.z*0.00001), lightdir, tnew, t1)) {
								//cout << "Test" << endl;
								transmission = glm::vec3(0.f, 0.f, 0.f);
								break;
							}
						}
					}
					retcol += abs(object->color * transmission * std::max(float(0), glm::dot(pn, lightdir)) * objects[i]->emissionColor);
				}
			}
		
		}

		//cout << "Funkar" << endl;
		//cout << retcol.x << endl << retcol.y << endl << retcol.z << endl;

		// Not shaded => return object's color
		
	}
	return retcol + object->emissionColor;
}
