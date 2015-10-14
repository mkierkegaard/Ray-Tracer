#include <stdlib.h>
#include <stdio.h>
#include <vector> 
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

glm::vec3 trace(glm::vec3 &rayorgin, glm::vec3 &raydir, const std::vector<Sphere> spheres) {

}

void render(const std::vector<Sphere> &spheres) {
	
	glm::vec3 *image = new glm::vec3[dimx * dimy], *pixel = image;
	for (unsigned x = 0; x < dimy; x++) {
		for (unsigned y = 0; y < dimx; y++) {
			float xx = x;
			float yy = y;
			glm::vec3 raydir(xx, yy, -1);
			*pixel = trace(glm::vec3(), raydir, spheres);

		}
	}

}
 
int main(void)
{
	std::vector<Sphere> spheres;
	spheres.push_back(Sphere(glm::vec3(0, 1, 2), 2, glm::vec3(20, 20, 20)));

	
	render(spheres);
	
  return EXIT_SUCCESS;
}