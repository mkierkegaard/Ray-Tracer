#include "Object.h"

Object::Object(){

}

Object::Object(glm::vec3 col) {
	color = col;
	cout << "s�tter en f�rg" << endl;
}