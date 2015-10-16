#include "Plane.h"
#include "Object.h"



Plane::Plane(glm::vec3 V1, glm::vec3 V2, glm::vec3 V3, glm::vec3 col) : Object (col)
{
	vertices1 = V1;
	vertices2 = V2;
	vertices3 = V3;
}

bool Plane::intersect(const glm::vec3 &rayorigin, const glm::vec3 &raydir, float &t0, float &t1)
{

	// compute plane's normal
	glm::vec3 v0v1 = this->vertices2 - this->vertices1;
	glm::vec3 v0v2 = this->vertices3 - this->vertices1;
	// no need to normalize
	glm::vec3 N = glm::cross(v0v1,v0v2); // N 
	float area2 = N.length();

	// Step 1: finding P

	// check if ray and plane are parallel ?
	float NdotRayDirection = glm::dot(N,raydir);
	if (fabs(NdotRayDirection) < 0.000001) // almost 0 
		return false; // they are parallel so they don't intersect ! 

					  // compute d parameter using equation 2
	float d = glm::dot(N, this->vertices1);
	// compute t (equation 3)
	t0 = glm::dot(N,rayorigin + d) / NdotRayDirection;
	// check if the triangle is in behind the ray
	if (t0 < 0) return false; // the triangle is behind 

							 // compute the intersection point using equation 1
	glm::vec3 P = rayorigin + t0 * raydir;

	// Step 2: inside-outside test
	glm::vec3 C; // vector perpendicular to triangle's plane 

			 // edge 1
	glm::vec3 edge1 = this->vertices2 - this->vertices1;
	glm::vec3 vp1 = P - this->vertices1;
	C = glm::cross(edge1,vp1);
	if (glm::dot(N,C) < 0) return false; // P is on the right side 

										   // edge 2
	glm::vec3 edge2 = this->vertices3 - this->vertices2;
	glm::vec3 vp2 = P - this->vertices2;
	C = glm::cross(edge2, vp2);
	if (glm::dot(N, C) < 0) return false; // P is on the right side 

											// edge 3
	glm::vec3 edge3 = this->vertices1 - this->vertices3;
	glm::vec3 vp3 = P - this->vertices3;
	C = glm::cross(edge3, vp3);
	if (glm::dot(N, C) < 0) return false; // P is on the right side 

	return true; // this ray hits the triangle 

}

Plane::~Plane()
{
}
