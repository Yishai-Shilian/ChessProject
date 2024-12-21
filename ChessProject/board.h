#pragma once
#include "GamePiece.h"
#include "ChessEnums.h"
#define BOARD_SIZE 8
#define PLACEMENT_STRING_SIZE 66

class Board
{
public:
	Board(const char placement[PLACEMENT_STRING_SIZE]);
	~Board();
	void printBoard();

private:
	GamePiece* _board[BOARD_SIZE][BOARD_SIZE];
};