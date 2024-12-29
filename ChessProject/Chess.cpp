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
		int frontendCode = this->CheckCode(this->_currPlayer,this->_board._board, sourcePose, destPose);
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
bool Chess::checkCode1(ChessColors currPlayer, int* srcPos, int* dstPos, GamePiece* board[BOARD_SIZE][BOARD_SIZE])
{
	if (madeChess(getOpponentColor(), srcPos, dstPos, board))
	{
		return FrontendCodes::validMoveCausesChessRival;
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

bool Chess::checkCode4(ChessColors currPlayer, int* srcPos, int* dstPos, GamePiece* board[BOARD_SIZE][BOARD_SIZE])
{
	return madeChess(currPlayer, srcPos, dstPos, board);
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

bool Chess::checkCode8(ChessColors currPlayer, int* srcPos, int* dstPos, GamePiece* board[BOARD_SIZE][BOARD_SIZE])
{
	return checkMate(currPlayer, board);
}

int Chess::CheckCode(ChessColors currPlayer,GamePiece* board[BOARD_SIZE][BOARD_SIZE], int* srcPos, int* dstPos) {
	if (checkCode2(board, srcPos)) {
		return FrontendCodes::sourceSquareNoCurrPiece;
	}
	else if (checkCode3(board, dstPos)) 
	{
		return FrontendCodes::destSquareHaveCurrPiece; 
	}
	else if (checkCode4(currPlayer, srcPos, dstPos, board))
	{
		return FrontendCodes::moveCauseChessCurrPlayer;
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
	//else if (checkCode8(currPlayer, dstPos, srcPos, board))
	//{
	//	return FrontendCodes::checkMate;
	//}
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
	GamePiece* movingPiece = nullptr;
	GamePiece* capturedPiece = nullptr;

	std::cout << "Starting madeChess function.\n";

	// Check if there is a piece to move
	movingPiece = board[srcPos[ROW_INDEX]][srcPos[COL_INDEX]];
	if (movingPiece == nullptr)
	{
		std::cout << "Source position is empty! Returning false.\n";
		return false; // Invalid move
	}

	// Deep copy the moving piece
	GamePiece* copiedPiece = movingPiece->clone();
	std::cout << "Deep copied the moving piece from (" << srcPos[ROW_INDEX] << ", " << srcPos[COL_INDEX] << ").\n";

	// Simulate the move
	capturedPiece = board[dstPos[ROW_INDEX]][dstPos[COL_INDEX]];
	board[dstPos[ROW_INDEX]][dstPos[COL_INDEX]] = movingPiece;
	board[srcPos[ROW_INDEX]][srcPos[COL_INDEX]] = nullptr;

	movingPiece->setPieceRow(dstPos[ROW_INDEX]);
	movingPiece->setPieceCol(dstPos[COL_INDEX]);

	std::cout << "Simulated move to (" << dstPos[ROW_INDEX] << ", " << dstPos[COL_INDEX] << ").\n";

	// Get the king's position
	std::cout << "Getting king's position for current player.\n";
	getPosKing(currPlayer, kingPos);
	std::cout << "King's position: (" << kingPos[ROW_INDEX] << ", " << kingPos[COL_INDEX] << ").\n";

	// Check if any opponent piece can attack the king's position
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			GamePiece* opponentPiece = board[i][j];
			if (opponentPiece != nullptr && opponentPiece->getColor() != currPlayer)
			{
				std::cout << "Checking opponent piece at (" << i << ", " << j << "). Name: "
					<< opponentPiece->getName() << ", color: " << opponentPiece->getColor() << "\n";

				if (opponentPiece->canMove(kingPos[ROW_INDEX], kingPos[COL_INDEX], board))
				{
					std::cout << "Opponent piece can attack the king!\n";
					isChess = true;
					break;
				}
			}
		}
		if (isChess)
		{
			break;
		}
	}

	// Undo the move to restore the original board state
	board[srcPos[ROW_INDEX]][srcPos[COL_INDEX]] = copiedPiece; // Restore the deep copied piece
	board[dstPos[ROW_INDEX]][dstPos[COL_INDEX]] = capturedPiece; // Restore the captured piece (if any)

	copiedPiece->setPieceRow(srcPos[ROW_INDEX]);
	copiedPiece->setPieceCol(srcPos[COL_INDEX]);

	std::cout << "Restored the original board state.\n";
	std::cout << "Returning " << (isChess ? "true" : "false") << ".\n";
	return isChess;
}






void Chess::getPosKing(ChessColors kingColor, int* pos)
{
	bool found = false;
	for (int i = 0; i < BOARD_SIZE && !found; i++)
	{
		for (int j = 0; j < BOARD_SIZE && !found; j++)
		{
			if (this->_board._board[i][j] != nullptr)
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
}
bool Chess::checkMate(ChessColors currPlayer, GamePiece* board[BOARD_SIZE][BOARD_SIZE])
{
	int kingPos[SIZE_POS];
	getPosKing(currPlayer, kingPos); // Get the current player's king position

	// Check if the king is in check first
	if (!madeChess(currPlayer, nullptr, nullptr, board)) // Assuming `madeChess` can check for general check
	{
		return false; // No check, so no checkmate
	}

	// Simulate all possible moves for the current player
	for (int srcRow = 0; srcRow < BOARD_SIZE; ++srcRow)
	{
		for (int srcCol = 0; srcCol < BOARD_SIZE; ++srcCol)
		{
			GamePiece* piece = board[srcRow][srcCol];
			if (piece != nullptr && piece->getColor() == currPlayer)
			{
				for (int destRow = 0; destRow < BOARD_SIZE; ++destRow)
				{
					for (int destCol = 0; destCol < BOARD_SIZE; ++destCol)
					{
						if (piece->canMove(destRow, destCol, board))
						{
							// Simulate the move
							GamePiece* capturedPiece = board[destRow][destCol];
							board[destRow][destCol] = piece;
							board[srcRow][srcCol] = nullptr;

							piece->setPieceRow(destRow);
							piece->setPieceCol(destCol);

							// Check if the king is still in check
							bool stillInCheck = madeChess(currPlayer, nullptr, nullptr, board);

							// Revert the move
							board[srcRow][srcCol] = piece;
							board[destRow][destCol] = capturedPiece;

							piece->setPieceRow(srcRow);
							piece->setPieceCol(srcCol);

							if (!stillInCheck)
							{
								return false; // Found a move that resolves the check
							}
						}
					}
				}
			}
		}
	}

	return true; // No valid moves found to resolve the check
}
