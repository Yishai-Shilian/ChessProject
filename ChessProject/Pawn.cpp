#include "Pawn.h"
#include <cmath> // For abs()
#include "ChessEnums.h"

// Constructor: Initializes a Pawn object with a name, color, position, and sets its first move status.
// Parameters:
// - name: The character representing the name of the piece.
// - color: The character representing the color of the piece.
// - row: The initial row position of the piece.
// - col: The initial column position of the piece.
Pawn::Pawn(const char name, const char color, const int row, const int col)
    : GamePiece(name, color, row, col), _isFirstMove(true)
{
}

// Copy Constructor: Creates a new Pawn object by copying another Pawn object.
// Parameters:
// - other: The Pawn object to copy.
Pawn::Pawn(const Pawn& other) : GamePiece(other), _isFirstMove(other._isFirstMove) {}

// Destructor: Cleans up resources used by the Pawn object.
Pawn::~Pawn() {}

// Checks if the Pawn can move to the specified position.
// Parameters:
// - newRow: The target row to move to.
// - newCol: The target column to move to.
// - board: The game board represented as a 2D array of pointers to GamePiece objects.
// Returns: True if the move is valid for a Pawn, false otherwise.
bool Pawn::canMove(const int newRow, const int newCol, GamePiece* board[BOARD_SIZE][BOARD_SIZE])
{
    int rowDiff = 0;
    int colDiff = 0;

    if (this->getColor() == ChessColors::white)
    {
        rowDiff = this->_pos[ROW_INDEX] - newRow;
        colDiff = this->_pos[COL_INDEX] - newCol;
    }
    else
    {
        rowDiff = newRow - this->_pos[ROW_INDEX];
        colDiff = newCol - this->_pos[COL_INDEX];
    }

    if (this->_isFirstMove == false)
    {
        if (colDiff == 0 && rowDiff == 1 && board[newRow][newCol] == nullptr)
        {
            return true;
        }

        if (rowDiff == 1 && abs(colDiff) == 1 && board[newRow][newCol] != nullptr && board[newRow][newCol]->getColor() != this->getColor())
        {
            return true;
        }
    }

    if (this->_isFirstMove)
    {
        if (rowDiff == 1 && colDiff == 0 && board[newRow][newCol] == nullptr)
        {
            this->_isFirstMove = false;
            return true;
        }

        if (rowDiff == DOUBLE_STEP_FIRST_MOVE && colDiff == 0 && board[newRow + getDir()][newCol] == nullptr && board[newRow][newCol] == nullptr)
        {
            this->_isFirstMove = false;
            return true;
        }

        if (rowDiff == 1 && abs(colDiff) == 1 && board[newRow][newCol] != nullptr && board[newRow][newCol]->getColor() != this->getColor())
        {
            this->_isFirstMove = false;
            return true;
        }
    }

    return false;
}

// Determines the movement direction of the Pawn based on its color.
// Returns: 1 if the Pawn is white, -1 if it is black.
int Pawn::getDir() const
{
    if (this->getColor() == ChessColors::white)
    {
        return 1;
    }
    return -1;
}

// Creates a copy of the Pawn object.
// Returns: A pointer to a new Pawn object that is a clone of the current object.
GamePiece* Pawn::clone() const
{
    return new Pawn(*this); // Create and return a copy of the current Pawn object
}
