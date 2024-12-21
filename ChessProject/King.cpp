#include "King.h"

King::King(const char name, const char color, const int row, const int col) : GamePiece(name, color, row, col)
{
}

King::~King()
{

}

bool King::canMove(int newRow, int newCul) const
{
	return false;
}

