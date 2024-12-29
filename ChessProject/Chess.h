#pragma once
#include "Board.h"
#include "Pipe.h"
#include "ChessEnums.h"
//#define STARTING_STRING "p##############################################################P1"
#define STARTING_STRING "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR0"
#define MSG_SIZE 1024

class Chess
{
public:
	Chess();
	~Chess();
	void play();
	void switchTurns();
	bool checkCode1(ChessColors currPlayer, int* srcPos, int* dstPos, GamePiece* board[BOARD_SIZE][BOARD_SIZE]);
	bool checkCode2(GamePiece* board[BOARD_SIZE][BOARD_SIZE],const int* srcPos);//checkIfEmpty
	bool checkCode3(GamePiece* board[BOARD_SIZE][BOARD_SIZE], const int* dstPos);//check if dstPos has the same color piece
	bool checkCode4(ChessColors currPlayer, int* srcPos, int* dstPos, GamePiece* board[BOARD_SIZE][BOARD_SIZE]); 
	bool checkCode5(const int* dstPos, const int* srcPos); //check Bounderies
	bool checkCode6(GamePiece* board[BOARD_SIZE][BOARD_SIZE], const int* srcPos,const int* dstPos);
	bool checkCode7(const int* dstPos,const int* srcPos);//same pos
	bool checkCode8(ChessColors currPlayer, int* srcPos, int* dstPos, GamePiece* board[BOARD_SIZE][BOARD_SIZE]);
	int CheckCode(ChessColors currPlayer,GamePiece* board[BOARD_SIZE][BOARD_SIZE], int* srcPos, int* dstPos);
	ChessColors getOpponentColor();
	bool madeChess(ChessColors currPlayer, int* srcPos, int* dstPos, GamePiece* board[BOARD_SIZE][BOARD_SIZE]);
	void getPosKing(ChessColors kingColor, int* pos);
	bool checkMate(ChessColors currPlayer, GamePiece* board[BOARD_SIZE][BOARD_SIZE]);
private:
	ChessColors _currPlayer;
	Board _board;
	Pipe _pipe;
};
