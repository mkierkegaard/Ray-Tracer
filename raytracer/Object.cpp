#include "Object.h"

Object::Object(){

}

Object::Object(glm::vec3 p, glm::vec3 col, glm::vec3 emcol, glm::vec3 refcol, float trans) {
	color = col;
	emissionColor = emcol;
	reflectanceColor = refcol;
	transparancy = trans;
	point = p;
}