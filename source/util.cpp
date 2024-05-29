#include "util.h"
#include "Tetromino.h"
#include <iostream>
using namespace std;
Util::Util()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "There was an error while initializing SDL : " << SDL_GetError();
	}
	else
	{
		window = SDL_CreateWindow("Cheap Tetris Spin-off", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, 0);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		if (window == NULL)
		{
			cout << "There was an error while creating the window : " << SDL_GetError();
		}
	}

	if (TTF_Init() < 0)
	{
		cout << "There was a TTF error : " << TTF_GetError();
	}

	rect.x = rect.y = rect.w = rect.h = 0;
	texture = NULL;
	textSurface = NULL;
	font = TTF_OpenFont("bit-pixel.ttf", 64);
	textColor = { 255, 255, 255, 255 };
}

void Util::UpdateRender()
{
	SDL_RenderPresent(renderer);
}

void Util::drawCurrentPiece(Tetromino tetro, int currentX, int currentY, int currentRotation)
{
	string currentTetro = tetro.currTetro();
	int currentNum = tetro.currentTetro;
	int index = tetro.currIndex();

	SDL_SetRenderDrawColor(renderer, pieceColors[currentNum].r, pieceColors[currentNum].g, pieceColors[currentNum].b, pieceColors[currentNum].a);
	for (int x = 0; x < index; x++)
		for (int y = 0; y < index; y++)
			if (currentTetro[tetro.rotation(x, y, currentRotation)] == 'X')
			{
				rect.x = (currentX + x) * GRID_SIZE;
				rect.y = (currentY + y) * GRID_SIZE + TOP_SPACE;
				rect.w = rect.h = GRID_SIZE;
				SDL_RenderFillRect(renderer, &rect);
			}
}

void Util::drawPlayBoard(Board gameBoard)
{
	for (int x = 0; x < BOARD_WIDTH; x++)
		for (int y = 0; y < BOARD_HEIGHT; y++)
		{
			int index = gameBoard.returnIndexAt(x, y);
			SDL_SetRenderDrawColor(renderer, boardColors[index].r, boardColors[index].g, boardColors[index].b, boardColors[index].a);

			rect.x = x * GRID_SIZE;
			rect.y = y * GRID_SIZE + TOP_SPACE;
			rect.w = rect.h = GRID_SIZE;
			SDL_RenderFillRect(renderer, &rect);
		}
}

void Util::drawNextPiece(int nextTetro)
{
	Tetromino tetro;
	tetro.currentTetro = nextTetro;
	string nextPiece = tetro.currTetro();
	int index = tetro.currIndex();

	SDL_SetRenderDrawColor(renderer, pieceColors[nextTetro].r, pieceColors[nextTetro].g, pieceColors[nextTetro].b, pieceColors[nextTetro].a);

	for (int x = 0; x < index; x++)
		for (int y = 0; y < index; y++)
			if (nextPiece[tetro.rotation(x, y, 0)] == 'X')
			{
				rect.x = (x + BOARD_WIDTH) * GRID_SIZE - 10;
        switch (nextTetro)
        {
            case 1:
                rect.y = (y * GRID_SIZE) + TOP_SPACE - 30;
                break;
            default:
                rect.y = (y * GRID_SIZE) + TOP_SPACE;
                break;
        }
				rect.w = rect.h = GRID_SIZE;
				SDL_RenderFillRect(renderer, &rect);
			}
}

void Util::drawHeldPiece(int heldPiece)
{
	Tetromino tetro;
	tetro.currentTetro = heldPiece;
	string nextPiece = tetro.currTetro();
	int index = tetro.currIndex();

	SDL_SetRenderDrawColor(renderer, pieceColors[heldPiece].r, pieceColors[heldPiece].g, pieceColors[heldPiece].b, pieceColors[heldPiece].a);
	for (int x = 0; x < index; x++)
		for (int y = 0; y < index; y++)
			if (nextPiece[tetro.rotation(x, y, 0)] == 'X')
			{
				rect.x = (x + BOARD_WIDTH) * GRID_SIZE - 10;
        switch (heldPiece) {
            case 1:
                rect.y = (y * GRID_SIZE) + TOP_SPACE * 2.5 - 30;
                break;
            default:
                rect.y = (y * GRID_SIZE) + TOP_SPACE * 2.5;
                break;
}

				rect.w = rect.h = GRID_SIZE;
				SDL_RenderFillRect(renderer, &rect);
			}
}


void Util::TopScreen()
{
	SDL_SetRenderDrawColor(renderer, border.r, border.g, border.b, border.a);
	for (int x = 0; x < SCREEN_WIDTH / GRID_SIZE; x++)
		for (int y = 0; y < TOP_SPACE / GRID_SIZE; y++)
		{
			if (x * GRID_SIZE > 10 || y * GRID_SIZE > 4)
			{
				rect.x = x * GRID_SIZE;
				rect.y = y * GRID_SIZE;
				rect.w = rect.h = GRID_SIZE;
				SDL_RenderFillRect(renderer, &rect);
			}
		}
}

void Util::drawShadowPiece(Tetromino tetro, Board gameBoard, int currentX, int currentY, int currentRotation)
{
	int index = tetro.currIndex();
	string currentTetro = tetro.currTetro();
	int possibleY = currentY;

	SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
	while (checkCollision(tetro, gameBoard, currentRotation, currentX, possibleY + 1))
		possibleY++;
	for (int x = 0; x < index; x++)
		for (int y = 0; y < index; y++)
			if (currentTetro[tetro.rotation(x, y, currentRotation)] == 'X')
			{
				rect.x = (currentX + x) * GRID_SIZE;
				rect.y = (possibleY + y) * GRID_SIZE + TOP_SPACE;
				rect.w = rect.h = GRID_SIZE;
				SDL_RenderDrawRect(renderer, &rect);
			}
}

void Util::writeText(string text, int x, int y, int w, int h)
{
	textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	rect.x = x;
	rect.y = y;
	rect.h = h;
	rect.w = w;
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(texture);
}

void Util::soundEffect(const char* path)
{
    Mix_Chunk* chunk = NULL;
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        cout << "Error initializing audio : " << Mix_GetError();
        return;
    }
    chunk = Mix_LoadWAV(path);
    if (chunk == NULL)
    {
        cout << "Error loading WAV file : " << Mix_GetError();
        return;
    }
    if (!Mix_Playing(-1))
    {
        if (Mix_PlayChannel(-1, chunk, 0) == -1)
        {
            cout << "Error playing WAV file : " << Mix_GetError();
        }
    }
    Mix_VolumeMusic(MIX_MAX_VOLUME / 10);
}

void Util::BGM()
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_Music* theme = Mix_LoadMUS("TetrisTheme.wav");
	Mix_PlayMusic(theme, -1);
	Mix_VolumeMusic(MIX_MAX_VOLUME / 8);
}

void Util::clearRenderer()
{
	SDL_SetRenderDrawColor(renderer, border.r, border.g, border.b, border.a);
	SDL_RenderClear(renderer);
}


void Util::destroy()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

