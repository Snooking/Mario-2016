#include "Drawing.h"

// narysowanie napisu txt na powierzchni screen, zaczynajπc od punktu (x, y)
// charset to bitmapa 128x128 zawierajπca znaki
void DrawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset) {
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while (*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
	};
};

// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt úrodka obrazka sprite na ekranie
void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, float x, float y) {
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
}

void DrawAnimatedSurface(SDL_Surface *screen, float x, float y, SDL_Surface *sprite, int move, bool side, int jump) {
	SDL_Rect s, d;
	int a = 0, b = 0;
	s.w = PIC_SIZE;
	s.h = PIC_SIZE;
	d.w = PIC_SIZE;
	d.h = PIC_SIZE;
	d.x = x - d.w / 2;
	d.y = y - d.h / 2;
	if (side)
		b = 0;
	else b = PIC_SIZE;
	if (jump == 1 || jump == 2)
		a = PIC_SIZE * 4;
	else if (move == 0)
		a = 0;
	else if (move % 10 < 3)
		a = PIC_SIZE;
	else if (move % 10 < 6)
		a = PIC_SIZE * 2;
	else if (move % 10 > 5)
		a = PIC_SIZE * 3;
	
	s.x = a;
	s.y = b;
		SDL_BlitSurface(sprite, &s, screen, &d);
};

// rysowanie pojedynczego pixela
void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color) {
	int bpp = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32 *)p = color;
};


// rysowanie linii o d≥ugoúci l w pionie (gdy dx = 0, dy = 1) 
// bπdü poziomie (gdy dx = 1, dy = 0)
void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	for (int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	};
};


// rysowanie prostokπta o d≥ugoúci bokÛw l i k
void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor) {
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};

void GetImage(SDL_Surface *&whereto, char *nameoffile) {
	whereto = SDL_LoadBMP(nameoffile);
	if (whereto == NULL) {
		printf("SDL_LoadBMP error: %s\n", SDL_GetError());
		SDL_Quit();
	};
	SDL_SetColorKey(whereto, true, 0x000000);
}