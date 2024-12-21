#pragma once
#include <iostream>
#include "Board.h"
#define SIZE_POS 2
#define ROW_INDEX 0
#define COL_INDEX 1
class GamePiece
{
public:
	GamePiece(const char name, const char color, const int row, const int col);
	virtual ~GamePiece();
	virtual bool canMove(int newRow,int newCul) const = 0;
	char getName() const;
	char getColor() const;
	int getPieceRow() const;
	int getPieceCol() const;

private:
	char _name;
	char _color;
	int _pos[SIZE_POS];
};
