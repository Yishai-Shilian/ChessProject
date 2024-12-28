#pragma once
#include "GamePiece.h"

class King : public GamePiece
{
public:
	King(const char name, const char color, const int row, const int col);
	~King();
	virtual bool canMove(const int newRow, const int newCol, GamePiece* board[BOARD_SIZE][BOARD_SIZE])  override;

private:
};

