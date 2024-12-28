#include "Chess.h"
#include <string>

Chess::Chess() : _board(STARTING_STRING), _currPlayer(ChessColors::white){}
Chess::~Chess() {}

void Chess::play()
{
	char msgToGraphics[MSG_SIZE];
	bool isConnect = this->_pipe.connect();
	std::string ans;
	while(!isConnect)
	{
		std::cout << "cant connect to graphics" << std::endl;
		std::cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << std::endl;
		std::cin >> ans;

		if (ans == "0")
		{
			std::cout << "trying connect again.." << std::endl;
			Sleep(5000);
			isConnect = this->_pipe.connect();
		}
		else
		{
			this->_pipe.close();
			return;
		}
	}

	strcpy_s(msgToGraphics, STARTING_STRING);
	this->_pipe.sendMessageToGraphics(msgToGraphics);   // send the board string

	this->_board.printBoard();

	// get message from graphics
	std::string msgFromGraphics = this->_pipe.getMessageFromGraphics();

	while(msgFromGraphics != "quit")
	{
		int sourcePose[2];
		Board::getPosFromString(msgFromGraphics.substr(0, SIZE_POS), sourcePose);
		int destPose[2];
		Board::getPosFromString(msgFromGraphics.substr(SIZE_POS, SIZE_POS + SIZE_POS), destPose);
		int frontendCode = this->CheckCode(this->_board._board, sourcePose, destPose);
		msgToGraphics[0] = (char)(frontendCode + '0');
		msgToGraphics[1] = 0;
		this->_pipe.sendMessageToGraphics(msgToGraphics);
		this->_board.printBoard();
		if (frontendCode == FrontendCodes::vaildMove)
		{
			this->switchTurns();
		}
		msgFromGraphics = this->_pipe.getMessageFromGraphics();
		
	}
	this->_pipe.close();
}

void Chess::switchTurns()
{
	if (this->_currPlayer == ChessColors::black)
	{
		this->_currPlayer = ChessColors::white;
	}
	else
	{
		this->_currPlayer = ChessColors::black;
	}
}

bool Chess::checkCode2(GamePiece* board[BOARD_SIZE][BOARD_SIZE],const int* srcPos)
{
	if (board[srcPos[ROW_INDEX]][srcPos[COL_INDEX]] == nullptr || board[srcPos[ROW_INDEX]][srcPos[COL_INDEX]]->getColor() != this->_currPlayer)
	{
		return true;
	}
	return false;
}

bool Chess::checkCode3(GamePiece* board[BOARD_SIZE][BOARD_SIZE], const int* dstPos)
{
	if (board[dstPos[ROW_INDEX]][dstPos[COL_INDEX]] != nullptr && 
		board[dstPos[ROW_INDEX]][dstPos[COL_INDEX]]->getColor() == this->_currPlayer)
	{
		return true;
	}
	return false;
}

bool Chess::checkCode5(const int* dstPos, const int* srcPos) {
	if (dstPos[ROW_INDEX] < 0 || dstPos[ROW_INDEX] >= BOARD_SIZE ||
		dstPos[COL_INDEX] < 0 || dstPos[COL_INDEX] >= BOARD_SIZE) {
		return true;
	}

	if (srcPos[ROW_INDEX] < 0 || srcPos[ROW_INDEX] >= BOARD_SIZE ||
		srcPos[COL_INDEX] < 0 || srcPos[COL_INDEX] >= BOARD_SIZE) {
		return true;
	}

	return false;	
}

bool Chess::checkCode6(GamePiece* board[BOARD_SIZE][BOARD_SIZE], const int* srcPos,const int* dstPos)
{
	if (!board[srcPos[ROW_INDEX]][srcPos[COL_INDEX]]->canMove(dstPos[ROW_INDEX], dstPos[COL_INDEX], board))
	{
		return true;
	}
	return false;
}

bool Chess::checkCode7(const int* dstPos, const int* srcPos)
{
	if (dstPos[ROW_INDEX] == srcPos[ROW_INDEX] && dstPos[COL_INDEX] == srcPos[COL_INDEX])
	{
		return true;
	}
	return false;
}

int Chess::CheckCode(GamePiece* board[BOARD_SIZE][BOARD_SIZE], const int* srcPos, const int* dstPos) {
	if (checkCode2(board, srcPos)) {
		return FrontendCodes::sourceSquareNoCurrPiece;
	}

	
	else if (checkCode3(board, dstPos)) 
	{
		return FrontendCodes::destSquareHaveCurrPiece; 
	}
	
	else if (checkCode5(dstPos, srcPos)) 
	{
		return FrontendCodes::illegalIndex; 
	}

	else if (checkCode6(board, srcPos, dstPos)) 
	{
		return FrontendCodes::illegalPieceMove;
	}
	
	else if (checkCode7(dstPos, srcPos)) 
	{
		return FrontendCodes::sourceDestSquareIdentical;
	}

	this->_board.movePiece(srcPos[ROW_INDEX], srcPos[COL_INDEX], dstPos[ROW_INDEX], dstPos[COL_INDEX]);
	return FrontendCodes::vaildMove;
}

ChessColors Chess::getOpponentColor()
{
	if (this->_currPlayer == ChessColors::black)
	{
		return ChessColors::white;
	}
	return ChessColors::black;
}

bool Chess::madeChess(ChessColors currPlayer, int* srcPos, int* dstPos, GamePiece* board[BOARD_SIZE][BOARD_SIZE])
{
	bool isChess = false;
	int kingPos[SIZE_POS];
	GamePiece* copiedBoard[BOARD_SIZE][BOARD_SIZE];
	Board::copyBoard(board, copiedBoard);
	getPosKing(currPlayer, kingPos);


}

void Chess::getPosKing(ChessColors kingColor, int* pos)
{
	bool found = false;
	for (int i = 0; i < BOARD_SIZE && !found; i++)
	{
		for (int j = 0; j < BOARD_SIZE && !found; j++)
		{
			if (this->_board._board[i][j]->getColor() == kingColor && 
				toupper(this->_board._board[i][j]->getName()) == 'K')
			{
				pos[ROW_INDEX] = i;
				pos[COL_INDEX] = j;
				found = true;
			}
		}
	}
}
