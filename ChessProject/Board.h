#pragma once
#include "GamePiece.h"
#include "Rook.h"
#include "King.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "Pawn.h"
#include "ChessEnums.h"
#define CULS_AND_ROWS_OF_BOARD 8
#define PLACEMENT_STRING_SIZE 66
#define COL_INDEX_STRING 0
#define ROW_INDEX_STRING 1

class Board
{
public:
	Board(const char placement[PLACEMENT_STRING_SIZE]);
	~Board();
	static void getPosFromString(const std::string posString, int* pos);
	void printBoard() const;
	void eat(const int row, const int col);
	void movePiece(const int sourceRow, const int sourceCol, const int destRow, const int destCol);
	static void copyBoard(GamePiece* boardCopiedFrom[BOARD_SIZE][BOARD_SIZE], GamePiece* copiedBoard[BOARD_SIZE][BOARD_SIZE]);
	GamePiece* getGamePiece(const int row, const int col) const;
	GamePiece* _board[BOARD_SIZE][BOARD_SIZE];
private:
};
