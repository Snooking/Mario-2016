#pragma once
#ifndef MARIO
#define MARIO

#define JUMPSTRENGTH 100
#define LIVES 3

#include "General.h"

class Mario {
public:
	int speed;
	int jump;
	int lives;
	int dead;
	float x;
	float y;
	float ystart;
	bool mariovscube;
	bool mariovscubeside;
	int move;
	// side = true dla mario patrz¹cego w prawo
	bool side;
	static char nameoffile[32];
	SDL_Surface *texture;
};

#endif 
