#pragma once
#ifndef CUBE
#define CUBE

#include "General.h"

class Cube {
public:
	float x;
	float y;
	SDL_Surface *texture;
	static char nameoffile[32];
	static char nameoffile_platform[32];

	void Load(float a, float b);
};

#endif
