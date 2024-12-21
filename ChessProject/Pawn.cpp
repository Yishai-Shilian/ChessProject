#include "Pawn.h"

Pawn::Pawn(const char name, const char color, const int row, const int col) : GamePiece(name, color, row, col) 
{
	this->_isFirstMove = true;
}
Pawn::~Pawn()
{
}

bool Pawn::canMove(int newRow, int newCol) const
{
	return false;
}

bool Pawn::isFirstMove() const
{
	return this->_isFirstMove;
}
