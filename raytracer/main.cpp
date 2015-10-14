#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <cassert> 
#include <algorithm>
#include <cmath>
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


glm::vec3 trace(glm::vec3 &rayorgin, glm::vec3 &raydir, const std::vector<Sphere> &spheres) {

	for (unsigned i = 0; i < spheres.size(); i++) {
		float t0 = INFINITY, t1 = INFINITY;
		if (spheres[i].intersect(rayorgin, raydir, t0, t1)) {
			return glm::vec3(1, 0, 0);
		}
		else {
			return glm::vec3(0, 0, 0);
		}
	}

}

void render(const std::vector<Sphere> &spheres) {
	
	glm::vec3 *image = new glm::vec3[dimx * dimy], *pixel = image;

	float invWidth = 1 / dimx;
	float invHeight = 1 / dimy;

	for (unsigned x = 0; x < dimx; x++) {
		for (unsigned y = 0; y < dimy; y++, pixel++) {
			float xx = (2 * ((x + 0.5) * invWidth) - 1);
			float yy = (1 - 2*((y + 0.5) * invHeight));



			glm::vec3 raydir(xx, yy, -1);
			*pixel = trace(glm::vec3(0,0,0), raydir, spheres);

		}
	}
	std::ofstream ofs("./untitled.ppm", std::ios::out | std::ios::binary);
	ofs << "P6\n" << dimx << " " << dimy << "\n255\n";
	for (unsigned i = 0; i < dimx * dimy; ++i) {
		ofs << (unsigned char)(std::min(float(1), image[i].x) * 255) <<
			(unsigned char)(std::min(float(1), image[i].y) * 255) <<
			(unsigned char)(std::min(float(1), image[i].z) * 255);
	}
	ofs.close();
	delete[] image;

}
 
int main(void)
{
	std::vector<Sphere> spheres;
	spheres.push_back(Sphere(glm::vec3(0, 0, -20), 0, glm::vec3(20, 20, 20)));

	
	render(spheres);
	
  return EXIT_SUCCESS;
}