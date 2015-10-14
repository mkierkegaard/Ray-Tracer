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
#include <glm/ext.hpp>

#if defined __linux__ || defined __APPLE__
// "Compiled for Linux
#else
// Windows doesn't define these values by default, Linux does
#define M_PI 3.141592653589793
#define INFINITY 1e8
#endif
const int dimx = 800, dimy = 800;


glm::vec3 trace(glm::vec3 &rayorgin, glm::vec3 &raydir, const std::vector<Sphere> &spheres) {

	float tnear = INFINITY;
	const Sphere* sphere = NULL;

	for (unsigned i = 0; i < spheres.size(); i++) {
		float t0 = INFINITY, t1 = INFINITY;
		if (spheres[i].intersect(rayorgin, raydir, t0, t1)) {
			if (t0 < 0) t0 = t1;
			if (t0 < tnear) {
				tnear = t0;
				sphere = &spheres[i];
			}
		}
	}
	if (!sphere) return glm::vec3(0, 0, 0);


	else return glm::vec3(1, 0, 0);
}

void render(const std::vector<Sphere> &spheres) {
	
	glm::vec3 *image = new glm::vec3[dimx * dimy], *pixel = image;

	float invWidth = 1 / float(dimx), invHeight = 1 / float(dimy);
	float fov = 30, aspectratio = dimx / float(dimy);
	float angle = tan(M_PI * 0.5 * fov / 180.);

	glm::mat4 projectionMatrix = glm::perspective(float(30), float(dimx) / float(dimy), float(0.1), 100.f);
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	glm::mat4 viewprojection = projectionMatrix * view;
	glm::mat4 viewprojectioninv = glm::inverse(viewprojection);


	for (unsigned y = 0; y < dimy; y++) {
		for (unsigned x = 0; x < dimx; x++, pixel++) {
			float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
			float yy = (1 - 2*((y + 0.5) * invHeight))*angle;

			glm::vec3 nearPlanePoint = (glm::vec3(float(x) / dimx, float(y) / dimy, 0) - glm::vec3(0.5, 0.5, 0.5)) * 2.0f;
			glm::vec3 farPlanePoint = (glm::vec3(float(x) / dimx, float(y) / dimy, 1) - glm::vec3(0.5, 0.5, 0.5)) * 2.0f;

			glm::vec4 nearPlanePointWorldSpace = viewprojectioninv * glm::vec4(nearPlanePoint, 1.0f);
			glm::vec4 farPlanePointWorldSpace4 = viewprojectioninv * glm::vec4(farPlanePoint, 1.0f);

			//GLM unproject för projection
			
			//glm::vec3 origin = glm::vec3(viewprojectioninv * glm::vec4((glm::vec3(float(x) / 800, float(y) / 800, 0) - glm::vec3(0.5, 0.5, 0)) * 2.0f, 1.0f));
								
			//glm::vec3 direction = glm::normalize(glm::vec3(viewprojectioninv * glm::vec4(glm::vec3(0,0,-1), 0)));

			glm::vec3 origin = nearPlanePointWorldSpace;
			glm::vec3 direction = glm::normalize(farPlanePointWorldSpace - nearPlanePointWorldSpace);

			//glm::vec3 raydir(x, y, -1);
			//glm::normalize(raydir);

			*pixel = trace(origin, direction, spheres);

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
	//spheres.push_back(Sphere(glm::vec3(0, 0, -2), 0.5, glm::vec3(20, 20, 20)));
	spheres.push_back(Sphere(glm::vec3(0.5, 0.5, -5), 0.2, glm::vec3(20, 20, 20)));
	
	render(spheres);
	
  return EXIT_SUCCESS;
}