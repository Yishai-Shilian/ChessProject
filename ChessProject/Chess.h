#pragma once
#include "Board.h"
#include "Pipe.h"
#include "ChessEnums.h"
//#define STARTING_STRING "p##############################################################P1"
#define STARTING_STRING "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR0"
#define MSG_SIZE 1024
#define CHAR_TO_NUM_CONVERTOR '0'

class Chess
{
public:
	Chess();
	~Chess();
	void play();
	void switchTurns();
	bool checkCode1(ChessColors currPlayer, const int* srcPos, const  int* dstPos, GamePiece* board[BOARD_SIZE][BOARD_SIZE]);
	bool checkCode2(GamePiece* board[BOARD_SIZE][BOARD_SIZE], const int* srcPos);//checkIfEmpty
	bool checkCode3(GamePiece* board[BOARD_SIZE][BOARD_SIZE], const int* dstPos);//check if dstPos has the same color piece
	bool checkCode4(const ChessColors currPlayer, const int* srcPos, const int* dstPos, GamePiece* board[BOARD_SIZE][BOARD_SIZE]);
	bool checkCode5(const int* dstPos, const int* srcPos); //check Bounderies
	bool checkCode6(GamePiece* board[BOARD_SIZE][BOARD_SIZE], const int* srcPos, const int* dstPos);
	bool checkCode7(const int* dstPos, const int* srcPos);//same pos
	int CheckCode(const ChessColors currPlayer, GamePiece* board[BOARD_SIZE][BOARD_SIZE], const int* srcPos, const int* dstPos);
	ChessColors getOpponentColor() const;
	bool madeChess(const ChessColors currPlayer, const int* srcPos, const  int* dstPos, GamePiece* board[BOARD_SIZE][BOARD_SIZE]);
	void getPosKing(const ChessColors kingColor, int* pos);

private:
	ChessColors _currPlayer;
	Board _board;
	Pipe _pipe;
};
