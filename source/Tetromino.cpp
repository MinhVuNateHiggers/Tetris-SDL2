#include "Tetromino.h"
using namespace std;
//    X..
//    XXX --> Hinh chu J
//    ...
Tetromino::Tetromino() : currentTetro(0)
{
    allTetros[0].append("....XXXX........"); // I shape
    allTetros[1].append(".....XX..XX....."); // O shape
    allTetros[2].append("X..XXX..."); // J shape
    allTetros[3].append("..XXXX..."); // L shape
    allTetros[4].append(".XXXX...."); // S shape
    allTetros[5].append("XX..XX..."); // Z shape
    allTetros[6].append(".X.XXX..."); // T shape
}

string Tetromino::currTetro()
{
    return allTetros[currentTetro];
}

int Tetromino::currIndex()
{
    if (currentTetro == 0 || currentTetro == 1)
        return 4;
    return 3;
}

//0 1 2       6 3 0
//3 4 5  -->  7 4 1
//6 7 8       8 5 2

int Tetromino::rotation(int x, int y, int currentRotation)
{
    int rotationIndex = currentRotation % 4;

    if (currentTetro == 0 || currentTetro == 1)
    {
        if (rotationIndex == 0)
        {
            return (y * 4) + x;
        }
        else if (rotationIndex == 1)
        {
            return 3 * 4 + y - (x * 4);
        }
        else if (rotationIndex == 2)
        {
            return 3 * 5 - (y * 4) - x;
        }
        else if (rotationIndex == 3)
        {
            return 3 - y + (x * 4);
        }
    }
    else
    {
        if (rotationIndex == 0)
        {
            return (y * 3) + x;
        }
        else if (rotationIndex == 1)
        {
            return 2 * 3 + y - (x * 3);
        }
        else if (rotationIndex == 2)
        {
            return 2 * 4 - (y * 3) - x;
        }
        else if (rotationIndex == 3)
        {
            return 2 - y + (x * 3);
        }
    }
    return -1;
}


