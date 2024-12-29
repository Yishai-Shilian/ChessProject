#include "King.h"
#include <cmath>

// Constructor: Initializes a King object with a name, color, and position.
// Parameters:
// - name: The character representing the name of the piece.
// - color: The character representing the color of the piece.
// - row: The initial row position of the King.
// - col: The initial column position of the King.
King::King(const char name, const char color, const int row, const int col)
    : GamePiece(name, color, row, col) {
}

// Copy Constructor: Creates a new King object by copying another King.
// Parameters:
// - other: The King object to copy.
King::King(const King& other)
    : GamePiece(other) {
}

// Destructor: Cleans up resources used by the King object.
King::~King() {}

// Checks if the King can move to the specified position.
// Parameters:
// - newRow: The target row to move to.
// - newCol: The target column to move to.
// - board: The game board represented as a 2D array of pointers to GamePiece objects.
// Returns: True if the King can move to the specified position, false otherwise.
bool King::canMove(const int newRow, const int newCol, GamePiece* board[BOARD_SIZE][BOARD_SIZE])
{
    int rowDiff = abs(newRow - this->_pos[ROW_INDEX]);
    int colDiff = abs(newCol - this->_pos[COL_INDEX]);
    if (rowDiff > 1 || colDiff > 1)
    {
        return false;
    }
    return true;
}

// Creates a clone of the current King object.
// Returns: A pointer to a new King object that is a copy of the current object.
GamePiece* King::clone() const
{
    return new King(*this);
}
