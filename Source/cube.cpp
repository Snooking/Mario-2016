#include "Cube.h"

char Cube::nameoffile[32] = "floor.bmp";
char Cube::nameoffile_platform[32] = "platform.bmp";

void Cube::Load(float a, float b) {
	this->x = a;
	this->y = b;
}