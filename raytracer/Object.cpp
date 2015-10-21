#include "Object.h"

Object::Object(){

}

Object::Object(glm::vec3 col) {
	color = col;
	cout << "sätter en färg" << endl;
}