#pragma once
#ifndef DRAWING
#define DRAWING

#include "General.h"


void DrawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset);
void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, float x, float y);
void DrawAnimatedSurface(SDL_Surface *screen, float x, float y, SDL_Surface *sprite, int move, bool side, int jump);
void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color);
void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color);
void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);
void GetImage(SDL_Surface *&whereto, char *nameoffile);
#endif 
