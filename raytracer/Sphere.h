#include <stdlib.h>
#include <stdio.h>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>

class Sphere
{
private:
	

protected:
	

public:
	Sphere::Sphere();
	Sphere::Sphere(glm::vec3 pos, float rad, glm::vec3 col);
	Sphere::~Sphere();
	float radius;
	glm::vec3 color;
	glm::vec3 getPos();
	glm::vec3 position;
	bool Sphere::intersect(const glm::vec3 &rayorigin, const glm::vec3 &raydir, float &t0, float &t1) const;
};

