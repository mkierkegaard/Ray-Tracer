#include <stdlib.h>
#include <stdio.h>
#include "Sphere.h"


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
	Sphere sphere = Sphere(glm::vec3(0,1, 2), 2, glm::vec3(20, 20, 20));
	// Checking checking...
	//houston plz
	//plzzzzzzzzzzz
	writeImage();
	
	
  return EXIT_SUCCESS;
}