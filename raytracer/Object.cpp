#include "Object.h"

Object::Object(){

}

Object::Object(glm::vec3 col, glm::vec3 emcol) {
	color = col;
	emissionColor = emcol;
	cout << "EMISSION color: " << emissionColor.x << endl;
}