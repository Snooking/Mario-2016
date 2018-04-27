#include "Core.h"

#define BLACK	SDL_MapRGB(general.screen->format, 0x00, 0x00, 0x00)
#define GREEN	SDL_MapRGB(general.screen->format, 0x00, 0xFF, 0x00)
#define RED		SDL_MapRGB(general.screen->format, 0xFF, 0x00, 0x00)
#define BLUE	SDL_MapRGB(general.screen->format, 0x00, 0xAA, 0xFF)
GeneralThreadData general;
Mario mario;
Lvl lvl;
Cube* cube = new Cube[FLOOR];
Cube* platform = new Cube[PLATFORMS];
//Enemy* enemy = new Enemy[ENEMIES];

//void GetLevelInfo(const char *name) {
//	int width=0, time=0, floor=0, platforms=0, enemies=0;
//	FILE * level = fopen(name, "r");
//	if (level) {
//		fscanf(level, "%d:%d:%d:%d:%d\n", & lvl.width, & lvl.time, &lvl.floor, & lvl.platforms, & lvl.enemies);
//		int number = 0;
//		fscanf(level, "%d\n", &lvl.numberofplatforms);
//		float lvl.*platform_x = new float[lvl.numberofplatforms];
//		for (int i = 0; i < lvl.numberofplatforms; i++){
//			fscanf(level, "%d\n",lvl.platform_x[i]);
//		}
//	}
//	else 
//		general.SetTheWorldFree();
//	fclose(level);
//}

void InitVariables() {
	lvl.time = LVL_TIME;
	lvl.width = LVL_WIDTH;
	lvl.platforms = PLATFORMS;
	lvl.floor = FLOOR;
	//lvl.enemies = ENEMIES;
	mario.y = SCREEN_HEIGHT / 2;
	mario.x = SCREEN_WIDTH / 2;
	general.worldTime = 0;
	general.t1 = SDL_GetTicks();
	general.quit = 0;
	mario.jump = 2;
	mario.lives = LIVES - mario.dead;
	mario.move = false;
}

void LevelInit(/*Cube cube[], Cube platform[]*/) {
	InitVariables();
	int j = 0, i = 0;
	int platform_length[10] = { 5,3,4,3,2,1,1,2,3,4 };
	int platform_x[10] = {350, 366, 1000, 1016, 1032, 1048, 1100, 1100, 1100, 1100};
	int platform_y[10] = {400, 320, 456, 440, 424, 408, 408, 424, 440, 456};
	for (int i = 0; i < lvl.floor; i++)
	{
		if (i < lvl.floor / 3 - 3)
			cube[i].Load(PIC_SIZE / 2 + PIC_SIZE * i, SCREEN_HEIGHT - PIC_SIZE / 2);
		else if (i > lvl.floor / 3 + 3)
			cube[i].Load(PIC_SIZE / 2 + PIC_SIZE * i, SCREEN_HEIGHT - PIC_SIZE / 2);
		else
		{
			cube[i].Load(lvl.width - PIC_SIZE*j, SCREEN_HEIGHT - PIC_SIZE / 2);
			j++;
		}
	}
	for (int k = 0; k < 10; k++)
	{
		for (int j = 0; j < platform_length[k]; j++) {
				platform[i].Load(platform_x[k] + PIC_SIZE*j, platform_y[k]);
				i++;
		}
	}
	//for (int i = 0; i < lvl.enemies; i++) {
	//	enemy[i].Load(1000 + 238 * i, 900 + 238 * i, 1100 + 238*i);
	//}
}

void DrawInfo() {
	lvl.timeleft = lvl.time - general.worldTime;
	// tekst informacyjny
	sprintf(general.text, "Time = %.1f s", lvl.timeleft);
	DrawString(general.screen, STRING_WIDTH - strlen(general.text) * 8 / 2, STRING_HEIGHT, general.text, general.charset);
	sprintf(general.text, "Lives: %i", mario.lives);
	DrawString(general.screen, general.screen->w - STRING_WIDTH - strlen(general.text) * 8 / 2, STRING_HEIGHT, general.text, general.charset);
}

void HowToDie(/*Cube cube[], Cube platform[]*/) {
	if (lvl.timeleft <= 0 || mario.y > SCREEN_HEIGHT) {
		mario.dead++;
		LevelInit(/*cube, platform*/);
	}
	if (mario.lives <= 0) {
		SDL_FillRect(general.screen, NULL, BLACK);
		sprintf(general.text, "Press n to start a new game");
		DrawString(general.screen, SCREEN_WIDTH/2 - strlen(general.text) * 8 / 2, SCREEN_HEIGHT/2, general.text, general.charset);
	}
}

void ReactToKey(/*Cube cube[], Cube platform[]*/) {
	while (SDL_PollEvent(&general.event)) {
		switch (general.event.type) {
		case SDL_KEYDOWN:
			if (general.event.key.keysym.sym == SDLK_ESCAPE) general.quit = 1;
			else if (general.event.key.keysym.sym == SDLK_RIGHT) {
				mario.move++;
				mario.side = true;
				mario.speed = 1;
			}
			else if (general.event.key.keysym.sym == SDLK_LEFT) {
				mario.move++;
				mario.side = false;
				mario.speed = -1;
			}
			else if (general.event.key.keysym.sym == 'n') {
				mario.dead = 0;
				LevelInit(/*cube, platform*/);
			}
			else if (general.event.key.keysym.sym == SDLK_UP && mario.jump == 0) {
				mario.jump = 1;
				mario.ystart = mario.y;
			}
			break;
		case SDL_KEYUP:
			if (general.event.key.keysym.sym == SDLK_LEFT || general.event.key.keysym.sym == SDLK_RIGHT) {
				mario.speed = 0;
				mario.move = 0;
				break;
			}
			else {
				break;
			}
		case SDL_QUIT:
			general.quit = 1;
			break;
		};
	};
}



void GetImages(/*Cube cube [], Cube platform []*/) {
	GetImage(general.charset, general.nameoffile);
	GetImage(mario.texture, mario.nameoffile);
	GetImage(cube[0].texture, cube[0].nameoffile);
	GetImage(platform[0].texture, platform[0].nameoffile_platform);
}

bool Collisions(double x1, double y1/*, Cube cube[], Cube platform[]*/) {

	int xl = (x1 - PIC_SIZE / 2);
	int yb = (y1 + PIC_SIZE / 2);
	
	int xr = (x1 + PIC_SIZE / 2);
	int yt = (y1 - PIC_SIZE / 2);
	
	for (int i = 0; i < lvl.floor; i++)
	{
		if ((cube[i].x + PIC_SIZE / 2) >= xl && (cube[i].y + PIC_SIZE / 2) >= yt &&
			(cube[i].x - PIC_SIZE / 2) <= xr && (cube[i].y - PIC_SIZE / 2) <= yb) {
			return true;
		}
	}
	for (int i = 0; i < lvl.platforms; i++)
	{
		if ((platform[i].x + PIC_SIZE / 2) >= xl && (platform[i].y + PIC_SIZE / 2) >= yt &&
			(platform[i].x - PIC_SIZE / 2) <= xr && (platform[i].y - PIC_SIZE / 2) <= yb) {
			return true;
		}
	}

	return false;
}

void ReactToCollisions(/*Cube cube[], Cube platform[]*/) {
	float tempX, tempY;
	tempX = mario.x;
	tempY = mario.y;
	tempX += mario.speed * general.delta * SCREEN_HEIGHT / 3;

	if (Collisions(tempX, tempY/*, cube, platform*/)) {
		tempX = mario.x;
	}

	if (mario.jump == 1) {
		if (tempY >= mario.ystart - JUMPSTRENGTH)
		{
			tempY -= SCREEN_HEIGHT / 2 * general.delta;
		}
		else mario.jump = 2;
	}
	else 
		tempY += SCREEN_HEIGHT / 2 * general.delta;

	if (Collisions(tempX, tempY/*, cube, platform*/)) {
		tempY = mario.y;
		mario.jump = 0;
	}
	
	mario.x = tempX;
	mario.y = tempY;
}

void CameraMove() {
	general.camera.x = mario.x - PIC_SIZE/2 - SCREEN_WIDTH/2;
	if (general.camera.x < 0)
	general.camera.x = 0;
	if (general.camera.x > lvl.width - SCREEN_WIDTH)
		general.camera.x = lvl.width - SCREEN_WIDTH;
}

void Drawing(/*Cube cube[], Cube platform[]*/) {
	DrawAnimatedSurface(general.screen, mario.x - general.camera.x, mario.y, mario.texture, mario.move, mario.side, mario.jump);
	for (int i = 0; i < lvl.floor; i++) {
		DrawSurface(general.screen, cube[0].texture, cube[i].x - general.camera.x, cube[i].y);
	}
	for (int i = 0; i < lvl.platforms; i++) {
		DrawSurface(general.screen, platform[0].texture, platform[i].x - general.camera.x, platform[i].y);
	}
	/*for (int i = 0; i < lvl.enemies; i++) {
		DrawSurface(general.screen, enemy[0].texture, enemy[i].x - general.camera.x, enemy[i].y);
	}*/
}

//void EnemyMove() {
//	for (int i = 0; i < lvl.enemies; i++) {
//		for (;;) {
//			if (enemy[i].x > enemy[i].xstart)
//				enemy[i].x += general.delta*SCREEN_HEIGHT / 3;
//			if (enemy[i].x < enemy[i].xend)
//				enemy[i].x -= general.delta*SCREEN_HEIGHT / 3;
//		}
//	}
//}

void LoadMario() {
	//GetLevelInfo("1.txt");
	LevelInit(/*cube[lvl.floor], platform[lvl.platforms]*/);
	general.CheckForInit();
	general.Fullscreen();
	general.GetInfo();

	GetImages(/*cube[lvl.floor], platform[lvl.platforms]*/);
	
	mario.dead = 0;
	while (!general.quit) {
		general.GetTime();
		SDL_FillRect(general.screen, NULL, BLUE);
		CameraMove();
		Drawing(/*cube[lvl.floor], platform[lvl.platforms]*/);
		DrawInfo();
		HowToDie(/*cube[lvl.floor], platform[lvl.platforms]*/);
		general.UpdateTextures();
		ReactToCollisions(/*cube[lvl.floor], platform[lvl.platforms]*/);
		ReactToKey(/*cube[lvl.floor], platform[lvl.platforms]*/);
	};
	delete cube;
	delete platform;
	general.SetTheWorldFree();
}
