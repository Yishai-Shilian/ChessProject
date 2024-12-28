#pragma once
#include "GamePiece.h"
class Queen : public GamePiece
{
public:
	Queen(const char name, const char color, const int row, const int col);
	~Queen();
	virtual bool canMove(const int newRow, const int newCol, GamePiece* board[BOARD_SIZE][BOARD_SIZE])  override;
private:
};
