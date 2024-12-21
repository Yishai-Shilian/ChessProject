#include "Board.h"
#include "Rook.h"
#include "King.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Queen.h"
#include "Knight.h"
Board::Board(const char placement[PLACEMENT_STRING_SIZE])
{
	int i, j = 0;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0;  j < BOARD_SIZE; j++)
		{
			switch (placement[j*i])
			{
			case whiteRook:
				this->_board[i][j] = new Rook(whiteRook,white,i,j);
				break;
			case blackRook:
				this->_board[i][j] = new Rook(blackRook, black, i, j);
				break;
			case whiteKing:
				this->_board[i][j] = new King(whiteKing, white, i, j);
				break;
			case blackKing:
				this->_board[i][j] = new King(blackKing, black, i, j);
				break;
			case whiteBishop:
				this->_board[i][j] = new Bishop(whiteBishop, white, i, j);
				break;
			case blackBishop:
				this->_board[i][j] = new Bishop(whiteBishop, white, i, j);
				break;
			case whitePawn:
				this->_board[i][j] = new Pawn(whitePawn, white, i, j);
				break;
			case blackPawn:
				this->_board[i][j] = new Pawn(blackPawn, black, i, j);
				break;
			case whiteQueen:
				this->_board[i][j] = new Queen(whiteQueen, white, i, j); //Yishai change it so it will work after u work on the queen class pls
				break;
			case blackQueen:
				this->_board[i][j] = new Queen(blackQueen, black, i, j); //same here
				break;
			case whiteKnight:
				this->_board[i][j] = new Knight(whiteKnight, white, i, j);
				break;
			case blackKnight:
				this->_board[i][j] = new Knight(whiteKnight, white, i, j);
			default:
				this->_board[i][j] = nullptr;
				break;
			}
		}
	}
}

Board::~Board()
{
	for (int row = 0; row < BOARD_SIZE; ++row)
	{
		for (int col = 0; col < BOARD_SIZE; ++col)
		{
			// Delete the GamePiece if it exists
			if (_board[row][col] != nullptr)
			{
				delete _board[row][col];
				_board[row][col] = nullptr; 
			}
		}
	}
}

void Board::printBoard()
{
	std::cout << "  ";
	// Print column headers (A-H for example)
	for (int col = 0; col < BOARD_SIZE; ++col)
	{
		std::cout << static_cast<char>('A' + col) << " ";
	}
	std::cout << "\n";

	// Print the board row by row
	for (int row = 0; row < BOARD_SIZE; ++row)
	{
		// Print the row number
		std::cout << (BOARD_SIZE - row) << " ";

		for (int col = 0; col < BOARD_SIZE; ++col)
		{
			if (_board[row][col] != nullptr)
			{
				// Print the name of the piece
				std::cout << _board[row][col]->getName() << " ";
			}
			else
			{
				// Print # for empty spaces
				std::cout << "# ";
			}
		}

		// End of the row
		std::cout << (BOARD_SIZE - row) << "\n";
	}

	// Print column headers again for clarity
	std::cout << "  ";
	for (int col = 0; col < BOARD_SIZE; ++col)
	{
		std::cout << static_cast<char>('A' + col) << " ";
	}
	std::cout << "\n";
}

