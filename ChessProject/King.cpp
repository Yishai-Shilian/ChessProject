#include "King.h"

King::King(const char name, const char color, const int row, const int col) : GamePiece(name, color,  row, col) {}

King::~King() {}

bool King::canMove(const int newRow, const int newCol, GamePiece* board[BOARD_SIZE][BOARD_SIZE]) 
{
	int rowDiff = abs(newRow - this->_pos[ROW_INDEX]);
	int colDiff = abs(newCol - this->_pos[COL_INDEX]);
	if (rowDiff > 1 || colDiff > 1)
	{
		return false;
	}
	return true;
}


