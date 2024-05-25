#include "game.h"
#include "util.h"
using namespace std;

bool checkCollision(Tetromino tetro, Board gameBoard, int currentRotation, int xPos, int yPos) {
    int index = tetro.currIndex();
    string currentTetro = tetro.currTetro();

    int x = 0;
    while (x < index) {
        int y = 0;
        while (y < index) {
            int tetroIndex = tetro.rotation(x, y, currentRotation);
            int cellIndex = gameBoard.returnIndexAt(xPos + x, yPos + y);

            if (xPos + x >= 0 && xPos + x < BOARD_WIDTH && yPos + y >= 0 && yPos + y < BOARD_HEIGHT) {
                if (currentTetro[tetroIndex] == 'X' && cellIndex != 0) {
                    return false;
                }
            }

            y++;
        }
        x++;
    }

    return true;
}


bool executeHardDrop(Tetromino tetro, Board gameBoard, int currentRotation, int currentX, int& currentY)
{
	while (checkCollision(tetro, gameBoard, currentRotation, currentX, currentY + 1))
		currentY++;
	return true;
}

void checkLines(Board gameBoard, vector<int> &lines, int &lineCounter, int& fallSpeed, int& level, int Index, int currentY)
{
    int y = 0;
    while (y < Index) {
        if (currentY + y < BOARD_HEIGHT - 1) {
            bool isLine = true;
            int x = 1;
            while (x < BOARD_WIDTH - 1) {
                int cellIndex = gameBoard.returnIndexAt(x, y + currentY);
                isLine &= (cellIndex != 0);
                x++;
            }
            if (isLine) {
                x = 1;
                while (x < BOARD_WIDTH - 1) {
                    gameBoard.markLine(x, y + currentY);
                    x++;
                }
                lineCounter++;
                if (lineCounter > 0 && lineCounter % 10 == 0 && fallSpeed > 1) {
                    fallSpeed--;
                    level = 21 - fallSpeed;
                }
                lines.push_back(currentY + y);
            }
        }
        y++;
    }


}

void eraseLines(Board gameBoard, vector<int>& lineStored)
{
	for (auto& l : lineStored)
	{
		for (int x = 1; x < BOARD_WIDTH - 1; x++)
		{
            int y = l;
            while (y > 0)
            {
                gameBoard.shiftCellDown(x, y);
                y--;
            }
			gameBoard.clearRow(x);
		}
		lineStored.clear();
	}
}
