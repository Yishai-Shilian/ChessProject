#include "Knight.h"

Knight::Knight(const char name, const char color, const int row, const int col) : GamePiece(name, color, row, col) {}

Knight::~Knight() {}

bool Knight::canMove(const int newRow, const int newCol, GamePiece* board[BOARD_SIZE][BOARD_SIZE]) 
{
	int rowDiff = abs(newRow - this->_pos[ROW_INDEX]);
	int colDiff = abs(newCol - this->_pos[COL_INDEX]);
	if ((rowDiff == diffCubes::two && colDiff == diffCubes::one) 
		|| (rowDiff == diffCubes::one && colDiff == diffCubes::two))
	{
		return true;
	}
	return false;
}

