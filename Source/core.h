#pragma once
#ifndef CORE
#define CORE

#include "General.h"
#include "Drawing.h"
#include "Mario.h"
#include "Cube.h"
#include "Level.h"
//#include "Enemy.h"

//void GetLevelInfo(const char * name);
void InitVariables();
void LevelInit(/*Cube cube[], Cube platform[]*/);
void DrawInfo();
void HowToDie(/*Cube cube[], Cube platform[]*/);

void ReactToKey(/*Cube cube[], Cube platform[]*/);

void GetImages(/*Cube cube[], Cube platform[]*/);
bool Collisions(double x1, double y1/*, Cube cube[], Cube platform[]*/);
void ReactToCollisions(/*Cube cube[], Cube platform[]*/);
void Drawing(/*Cube cube[], Cube platform[]*/);
void LoadMario();

#endif 
