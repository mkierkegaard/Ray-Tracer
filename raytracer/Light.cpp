#include "Light.h"
#include "Object.h"


Light::Light(glm::vec3 p, glm::vec3 c)
{
	position = p;
	color = c;
}

Light::~Light()
{
}
