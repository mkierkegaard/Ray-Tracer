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
#include <iostream>
#include "Sphere.h"
#include "Plane.h"
#include "Ray.h"
#include "Light.h"
#include "World.h"
#include "Object.h"
#include <glm/ext.hpp>

using namespace std;

#if defined __linux__ || defined __APPLE__
// "Compiled for Linux
#else
// Windows doesn't define these values by default, Linux does
#define M_PI 3.141592653589793
#define INFINITY 1e8
#endif
const int dimx = 800, dimy = 800;


/*glm::vec3 trace(glm::vec3 &rayorgin, glm::vec3 &raydir, std::vector<Object*> &objects) {

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


	else
	{
		// p is the point of intersection
		// pDir is a normalized vector from p towards light source
		glm::vec3 p = rayorgin + raydir * tnear;
		glm::vec3 pdir = lightpos1 - p;
		float dist = glm::length(pdir);
		pdir = glm::normalize(pdir);

		// Look through all objects, if we find an object closer than the light source, shaded = true;
		for (auto &o : *world->objects)
			if (o->intersects(p, pdir, t0, t1))
				if (t0 < dist) return glm::vec3(0.0, 0.0, 0.0);

		// Not shaded => return object's color
	}
}*/

/*void render(std::vector<Object*> &objects) {
	
	glm::vec3 *image = new glm::vec3[dimx * dimy], *pixel = image; 

	//float invWidth = 1 / float(dimx), invHeight = 1 / float(dimy);
	//float fov = 30, aspectratio = dimx / float(dimy);
	//float angle = tan(M_PI * 0.5 * fov / 180.);

	glm::mat4 projectionMatrix = glm::perspective(float(30), float(dimx) / float(dimy), float(0.1), 100.f);
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	glm::mat4 viewprojection = view * projectionMatrix;// *view;
	glm::mat4 viewprojectioninv = glm::inverse(viewprojection);


	for (unsigned y = 0; y < dimy; y++) {
		for (unsigned x = dimx; x > 0; x--, pixel++) {
			//float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
			//float yy = (1 - 2*((y + 0.5) * invHeight))*angle;

			glm::vec3 to = glm::unProject(glm::vec3(x, y, 1), view, projectionMatrix, glm::vec4(0, 0, dimx, dimy));
			glm::vec3 from = glm::unProject(glm::vec3(x, y, -1), view, projectionMatrix, glm::vec4(0, 0, dimx, dimy));

			//glm::vec3 nearPlanePoint = (glm::vec3((float(x) / dimx) - 0.5f, (float(y) / dimy) -0.5f, 0.5f) * 2.f); //- glm::vec3(0.5, 0.5, 0.5)) * 2.0f;
			//glm::vec3 farPlanePoint = (glm::vec3((float(x) / dimx) - 0.5f, (float(y) / dimy) - 0.5f, -0.5f) * 2.f); //- glm::vec3(0.5, 0.5, 0.5)) * 2.0f;

			//glm::vec4 nearPlanePointWorldSpace = viewprojectioninv * glm::vec4(nearPlanePoint, 1.0f);
			//glm::vec4 farPlanePointWorldSpace4 = viewprojectioninv * glm::vec4(farPlanePoint, 1.0f);

			//GLM unproject f�r projection
			
			//glm::vec3 origin = glm::vec3(viewprojectioninv * glm::vec4((glm::vec3(float(x) / 800, float(y) / 800, 0) - glm::vec3(0.5, 0.5, 0)) * 2.0f, 1.0f));
								
			//glm::vec3 direction = glm::normalize(glm::vec3(viewprojectioninv * glm::vec4(glm::vec3(0,0,-1), 0)));
			//float nearh = nearPlanePointWorldSpace.w;
			//float farh = farPlanePointWorldSpace4.w;

			glm::vec3 origin = from; //glm::vec3(nearPlanePointWorldSpace)*nearh;
			glm::vec3 direction = glm::normalize(to - from);//glm::normalize(glm::vec3(farPlanePointWorldSpace4)*farh - glm::vec3(nearPlanePointWorldSpace)*nearh);

			//glm::vec3 raydir(x, y, -1);
			//glm::normalize(raydir);

			Ray ray(&world);

			*pixel = trace(origin, direction, objects);

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

}*/
 
int main(void)
{

	World world;
	Object* o;
	//Light* l;

	world.lightpos1.x = -1.5f;
	world.lightpos1.y = 4.5f;
	world.lightpos1.z = -5.5f;

	world.lightpos2.x = 1.5f;
	world.lightpos2.y = 4.5f;
	world.lightpos2.z = -5.5f;

	//l = new Light(glm::vec3(world.lightpos), glm::vec3(0.4, 0.2, 0.5));
	//world.addLight(*l);

	o = new Sphere(glm::vec3(2, 0, -6), 1.5, glm::vec3(0.2, 0.2, 0.9), glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), 0.f);
	world.addObject(*o);
	
	o = new Sphere(glm::vec3(-3, -3, -6), 1.5, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.2, 0.2, 0.2), 1.f);
	world.addObject(*o);

	o = new Sphere(glm::vec3(4.5, 3, -6), 0.5, glm::vec3(0.35, 0.2, 0.25), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), 0);
	world.addObject(*o);

	o = new Sphere(glm::vec3(world.lightpos1.x, world.lightpos1.y, world.lightpos1.z), 0.5, glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.0, 0.0, 0.0), 0);
	world.addObject(*o);

	o = new Sphere(glm::vec3(world.lightpos2.x, world.lightpos2.y, world.lightpos2.z), 0.5, glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.0, 0.0, 0.0), 0);
	world.addObject(*o);
	
	//normal, f�rg, punkt p� planet, emission

	o = new Plane(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.0, 0.0, -10), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), 0);
	world.addObject(*o);

	o = new Plane(glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.05, 0.05, 0.05), glm::vec3(0.0, -5, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), 0);
	world.addObject(*o);

	o = new Plane(glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.05, 0.15, 0.05), glm::vec3(0.0, 5, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), 0);
	world.addObject(*o);

	o = new Plane(glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.15, 0.05, 0.05), glm::vec3(5, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), 0);
	world.addObject(*o);

	o = new Plane(glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.05, 0.05, 0.15), glm::vec3(-5, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), 0);
	world.addObject(*o);

	//Ray ray(world);

	glm::vec3 *image = new glm::vec3[dimx * dimy], *pixel = image;

	glm::mat4 projectionMatrix = glm::perspective(float(30), float(dimx) / float(dimy), float(0.1), 100.f);
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	glm::mat4 viewprojection = view * projectionMatrix;// *view;
	glm::mat4 viewprojectioninv = glm::inverse(viewprojection);

	
	#pragma omp parallel for
	for (int y = 0; y < dimy; y++) {
		for (unsigned x = 0; x < dimx; x++) {

			glm::vec3 color = glm::vec3(0.0, 0.0, 0.0);
			int samples = 9;


			// shoot rays into scene
			for (int i = 0; i < samples; i++) {

				float randomX = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				float randomY = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				
				glm::vec3 to = glm::unProject(glm::vec3(x + randomX, (float)y + randomY, 1), view, projectionMatrix, glm::vec4(0, 0, dimx, dimy));
				glm::vec3 from = glm::unProject(glm::vec3(x + randomX, (float)y + randomY, -1), view, projectionMatrix, glm::vec4(0, 0, dimx, dimy));

				glm::vec3 origin = from;
				glm::vec3 direction = glm::normalize(to - from);
				Ray ray(world);

				color += ray.trace(origin, direction, world.objects, 0);
			}

			color /= samples;
			pixel[y*dimx + x] = color;

		}
		//cout << "y : " << y << endl;;
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

  return EXIT_SUCCESS;
}