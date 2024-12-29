#include "Queen.h"
#include <cmath>

// Constructor: Initializes a Queen object with a name, color, and position.
// Parameters:
// - name: The character representing the name of the piece.
// - color: The character representing the color of the piece.
// - row: The initial row position of the piece.
// - col: The initial column position of the piece.
Queen::Queen(const char name, const char color, const int row, const int col)
    : GamePiece(name, color, row, col) {
}

// Copy Constructor: Creates a new Queen object by copying another Queen object.
// Parameters:
// - other: The Queen object to copy.
Queen::Queen(const Queen& other) : GamePiece(other) {}

// Destructor: Cleans up resources used by the Queen object.
Queen::~Queen() {}

// Checks if the Queen can move to the specified position.
// Parameters:
// - newRow: The target row to move to.
// - newCol: The target column to move to.
// - board: The game board represented as a 2D array of pointers to GamePiece objects.
// Returns: True if the move is valid for a Queen, false otherwise.
bool Queen::canMove(const int newRow, const int newCol, GamePiece* board[BOARD_SIZE][BOARD_SIZE])
{
    int rowDiff = abs(newRow - this->_pos[ROW_INDEX]);
    int colDiff = abs(newCol - this->_pos[COL_INDEX]);

    if ((this->_pos[ROW_INDEX] == newRow || this->_pos[COL_INDEX] == newCol) ||
        rowDiff == colDiff)
    {
        if (IsPathClear(newRow, newCol, board))
        {
            return true;
        }
    }
    return false;
}

// Creates a copy of the Queen object.
// Returns: A pointer to a new Queen object that is a clone of the current object.
GamePiece* Queen::clone() const
{
    return new Queen(*this);
}
