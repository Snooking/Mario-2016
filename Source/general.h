#pragma once
#ifndef GENERAL
#define GENERAL

#include<stdio.h>
#include<string.h>

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480
#define CUBES 5

#define PIC_SIZE 16
#define STRING_WIDTH 75
#define STRING_HEIGHT 10

extern "C" {
#include"./sdl/include/SDL.h"
#include"./sdl/include/SDL_main.h"
}

class GeneralThreadData{
public:
	int t1;
	int	t2;
	int	quit;
	int	rc;
	static int fullscreen;
	double delta;
	double worldTime;
	char text[128];
	static char nameoffile[32];
	SDL_Event event;
	SDL_Surface *screen;
	SDL_Surface	*charset;
	SDL_Surface *eti;
	SDL_Texture *scrtex;
	SDL_Window *window;
	SDL_Renderer *renderer;
	static SDL_Rect camera;


	int CheckForInit();
	int Fullscreen();
	void GetInfo();
	void GetTime();
	void UpdateTextures();
	void SetTheWorldFree();
};

#endif