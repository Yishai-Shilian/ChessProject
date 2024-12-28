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
	//need to add code 1
	bool checkCode2(GamePiece* board[BOARD_SIZE][BOARD_SIZE],const int* srcPos);//checkIfEmpty
	bool checkCode3(GamePiece* board[BOARD_SIZE][BOARD_SIZE], const int* dstPos);//check if dstPos has the same color piece
	bool checkCode4(); //hell
	bool checkCode5(const int* dstPos, const int* srcPos); //check Bounderies
	bool checkCode6(GamePiece* board[BOARD_SIZE][BOARD_SIZE], const int* srcPos,const int* dstPos);
	bool checkCode7(const int* dstPos,const int* srcPos);//same pos
	int CheckCode(GamePiece* board[BOARD_SIZE][BOARD_SIZE], const int* srcPos, const int* dstPos);
	ChessColors getOpponentColor();
	bool madeChess(ChessColors currPlayer);
	void getPosKing(ChessColors kingColor, int* pos);
private:
	ChessColors _currPlayer;
	Board _board;
	Pipe _pipe;
};
