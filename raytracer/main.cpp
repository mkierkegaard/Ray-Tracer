#include <stdlib.h>
#include <stdio.h>
#include "Sphere.h"
#include <glm/vec3.hpp>


const int dimx = 800, dimy = 800;

void writeImage() {	

	int i, j;
	FILE *fp = fopen("first.ppm", "wb"); /* b - binary mode */
	(void)fprintf(fp, "P6\n%d %d\n255\n", dimx, dimy);

	int** img = new int*[dimx];
	for (int i = 0; i < dimx; ++i)
		img[i] = new int[dimy];

	for (j = 0; j < dimy; ++j)
	{
		for (i = 0; i < dimx; ++i)
		{
			img[j][i] = i*j;
			static unsigned char color[3];
			color[0] = i % 256;  /* red */
			color[1] = j % 256;  /* green */
			color[2] = (i * j) % 256;  /* blue */
			(void)fwrite(img, 1, 3, fp);
		}
	}
	(void)fclose(fp);
}
 
int main(void)
{
	Sphere sphere = Sphere(glm::vec3(0.0, -10004, -20), 10000, glm::vec3(0.20, 0.20, 0.20));
	// Checking checking...
	//houston plz
	//plzzzzzzzzzzz
	writeImage();
	
	
  return EXIT_SUCCESS;
}