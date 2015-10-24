#include "Object.h"

Object::Object(){

}

Object::Object(glm::vec3 col, glm::vec3 emcol, glm::vec3 refcol) {
	color = col;
	emissionColor = emcol;
	reflectanceColor = refcol;
}