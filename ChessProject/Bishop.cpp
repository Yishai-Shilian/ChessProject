#include "Bishop.h"

Bishop::Bishop(const char name, const char color, const int row, const int col) : GamePiece(name, color, row, col)
{
}

Bishop::~Bishop()
{
}

bool Bishop::canMove(int newRow, int newCul) const
{
	return false;
}

