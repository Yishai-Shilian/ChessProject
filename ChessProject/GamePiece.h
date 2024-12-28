#pragma once
#include <iostream>
#include "ChessEnums.h"
#define SIZE_POS 2
#define ROW_INDEX 0
#define COL_INDEX 1

class GamePiece
{
public:
	GamePiece(const char name, const char color, const int row, const int col);
	virtual ~GamePiece();
	virtual bool canMove(const int newRow,const int newCol, GamePiece* board[BOARD_SIZE][BOARD_SIZE]) = 0;
	char getName() const;
	char getColor() const;
	void setPieceRow(const int newRow);
	void setPieceCol(const int newCol);
	bool IsPathClear(const int newRow, const int newCol, GamePiece* board[BOARD_SIZE][BOARD_SIZE]);

private:
	char _name;
	char _color;
protected:
	int _pos[SIZE_POS];
};
