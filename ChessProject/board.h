#pragma once
#include "GamePiece.h"
#define BOARD_SIZE 8
#define PLACEMENT_STRING_SIZE 66

class Board
{
public:
	Board(const char placement[PLACEMENT_STRING_SIZE]);
	~Board();

private:
	GamePiece* _board[BOARD_SIZE][BOARD_SIZE];
};