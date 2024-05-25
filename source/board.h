#pragma once
#include "Tetromino.h"

const int BOARD_WIDTH = 12;
const int BOARD_HEIGHT = 21;

class Board
{
private:
	char* playBoard;
public:
	Board();
	void addNewPiece(Tetromino tetro, int currentRotation, int currentX, int currentY);
	int returnIndexAt(int x, int y);
	void markLine(int x, int y);
	void shiftCellDown(int x, int y);
	void clearRow(int x);
};
