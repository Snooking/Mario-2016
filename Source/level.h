#pragma once
#ifndef LEVEL
#define LEVEL

#include "General.h"

#define FLOOR 120
#define PLATFORMS 28
#define ENEMIES 2
#define LVL_WIDTH 2000
#define LVL_TIME 45

class Lvl {
public:
	int width;
	int time;
	int floor;
	int platforms;
	int enemies;
	//int numberoffloors;
	//int numberofplatforms;
	float timeleft;
	//float platform_x[];
};

#endif