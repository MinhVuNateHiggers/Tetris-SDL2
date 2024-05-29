#pragma once
#include "colors.h"
#include "Tetromino.h"
#include "board.h"
#include "game.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
using namespace std;

const int GRID_SIZE = 30; // Kich thuoc o
const int TOP_SPACE = 120; // Khoang cach tu dinh cua so den board
const int SCREEN_HEIGHT = 750;
const int SCREEN_WIDTH = 500;

struct Util
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Rect rect;
	SDL_Texture* texture;
	SDL_Surface* textSurface;
	TTF_Font* font;
	SDL_Color textColor;
public:
	Util();
	void UpdateRender();
	void drawCurrentPiece(Tetromino tetro, int currentX, int currentY, int currentRotation);
	void drawPlayBoard(Board gameBoard);
	void drawNextPiece(int nextNum);
    void drawHeldPiece(int heldPiece);
	void TopScreen();
	void drawShadowPiece(Tetromino tetro, Board gameBoard, int currentX, int currentY, int currentRotation);
	void writeText(string text, int x, int y, int w, int h);
	void soundEffect(const char* path);
	void BGM();
	SDL_Texture* loadTexture(string path, SDL_Renderer* renderer);
	void clearRenderer();
	void destroy();
};


