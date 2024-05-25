#pragma once
#include "util.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <bits/stdc++.h>
using namespace std;

enum class GameState {START_MENU, IN_GAME, GAME_OVER, QUIT};

bool checkCollision(Tetromino tetro, Board gameBoard, int currentRotation, int xPos, int yPos);
bool executeHardDrop(Tetromino tetro, Board gameBoard, int currentRotation, int currentX, int& currentY);
void checkLines(Board gameBoard, vector<int>& lines, int& lineCount, int& speed, int& level, int maxIndex, int currentY);
void eraseLines(Board gameBoard, vector<int>& storeLine);
void Loop();
