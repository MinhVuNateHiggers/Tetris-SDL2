#include "board.h"
using namespace std;
//Su dung mang 1 chieu de mo phong mang 2 chieu
//Cap phat bo nho cho con tro voi kich thuoc bang tong so o vuong trong man choi
//Anh xa x,y vao chi so 1 chieu cua mang
Board::Board() {
    playBoard = new char[BOARD_WIDTH * BOARD_HEIGHT];
    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_HEIGHT; y++) {
            if (x == 0 || x == BOARD_WIDTH - 1 || y == BOARD_HEIGHT - 1) {
                playBoard[(y * BOARD_WIDTH) + x] = 8;
            } else {
                playBoard[(y * BOARD_WIDTH) + x] = 0;
            }
        }
    }
}


void Board::addNewPiece(Tetromino tetro, int currentRotation, int currentX, int currentY)
{
	string thisTetromino = tetro.currTetro();
	int index = tetro.currIndex(); // gia tri la 4 hoac 3

	for (int x = 0; x < index; x++)
		for (int y = 0; y < index; y++)
			if (thisTetromino[tetro.rotation(x, y, currentRotation)] == 'X')
			{
				playBoard[(currentY + y) * BOARD_WIDTH + (currentX + x)] = tetro.currentTetro + 1;
			}
            // Sau khi duyet xem cac o vuong co ki tu 'X' hay khong, se them gia tri cua khoi Tetromino vao bang choi dua vao vi tri hien tai, goc quay hien tai
            // +1 vi chi so cua cac khoi tetromino bat dau tu 0, tranh xung dot voi cac o trong
            // VD : Khi them khoi hinh chu I co gia tri = 0 vao bang se co gia tri la 1 tai vi tri tuong ung
}

int Board::returnIndexAt(int x, int y)
{
	return playBoard[x + (BOARD_WIDTH * y)];
}

void Board::markLine(int x, int y)
{
	playBoard[(y * BOARD_WIDTH) + x] = 9;

}

void Board::shiftCellDown(int x, int y)
{
	playBoard[y * BOARD_WIDTH + x] = playBoard[(y - 1) * BOARD_WIDTH + x];
}

void Board::clearRow(int x)
{
	playBoard[x] = 0;
}

