#pragma once

#define BOARD_SIZE 8

enum whiteGamePieces
{
	whiteKing = 'K',
	whiteQueen = 'Q',
	whiteRook = 'R',
	whiteKnight = 'N',
	whiteBishop = 'B',
	whitePawn = 'P'
};

enum blackGamePieces
{
	blackKing = 'k',
	blackQueen = 'q',
	blackRook = 'r',
	blackKnight = 'n',
	blackBishop = 'b',
	blackPawn = 'p'
};

enum ChessColors
{
	white = 'w',
	black = 'b'
};

enum FrontendCodes
{
	vaildMove,
	validMoveCausesChessRival,
	sourceSquareNoCurrPiece,
	destSquareHaveCurrPiece,
	moveCauseChessCurrPlayer,
	illegalIndex,
	illegalPieceMove,
	sourceDestSquareIdentical,
	checkMate,
};