#include "Bishop.h"

Bishop::Bishop(const char name, const char color, const int row, const int col): GamePiece(name, color, row, col) {}

Bishop::~Bishop() {}

bool Bishop::canMove(const int newRow, const int newCol, GamePiece* board[BOARD_SIZE][BOARD_SIZE]) 
{
	int rowDiff = abs(newRow - this->_pos[ROW_INDEX]);
	int colDiff = abs(newCol - this->_pos[COL_INDEX]);
	if (rowDiff != colDiff || !IsPathClear(newRow, newCol, board))
	{
		return false;
	}
	return true;
}




