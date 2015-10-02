#include <stdlib.h>
#include <stdio.h>
#include "Sphere.h"
#include "Ray.h"

#if defined __linux__ || defined __APPLE__
// "Compiled for Linux
#else
// Windows doesn't define these values by default, Linux does
#define M_PI 3.141592653589793
#define INFINITY 1e8
#endif
const int dimx = 800, dimy = 800;

void render() {
	for (int i = 0; i < dimx; i++) {
		for (int j = 0; j < dimy; i++) {
			Ray primray;
			computeRaydir(i, j, &primray);
			glm::vec3 pHit;
			glm::vec3 nHit;
			float minDistance = INFINITY;
			Sphere sphere = NULL;
			for (int k = 0; k < spheres.size(); k++) {
				if (intersect(sphere[k], primray, &pHit, &nHit)) {
					float distance = Distance(eyePosition, pHit);
					if (distance < minDistance) {
						sphere = spheres[k];
						minDistance = distance;
					}
				}
			}
			if (sphere != NULL) {
				Ray shadowray;
				shadowray.direction = LightPosition - pHit;
				bool IsShadow = false;
				for (int k = 0; k < spheres.size(); k++) {
					if (intersect(sphere[k], shadowray)) {
						isInShadow = true;
						break;
					}
				}
			}
			if (!isInShadow)
				pixels[i][j] = sphere->color * light.brightness;
			else
				pixels[i][j] = 0;
		}
	}

}
 
int main(void)
{
	Sphere sphere = Sphere(glm::vec3(0, 1, 2), 2, glm::vec3(20, 20, 20));
	// Checking checking...
	//houston plz
	//plzzzzzzzzzzz
	render();
	
  return EXIT_SUCCESS;
}