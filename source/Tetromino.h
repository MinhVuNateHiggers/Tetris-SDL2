#pragma once
#include <string>
using namespace std;
class Tetromino
{
private :
	string allTetros[7];
public:
	int currentTetro;
	Tetromino();
	string currTetro();
	int currIndex();
	int rotation(int x, int y, int currentRotation);
};
