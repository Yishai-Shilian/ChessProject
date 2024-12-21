#include "Rook.h"

Rook::Rook(const char name, const char color, const int row, const int col) : GamePiece(name,color,row,col)
{
}

Rook::~Rook()
{
}

bool Rook::canMove(int newRow, int newCul) const
{
	return false;
}

