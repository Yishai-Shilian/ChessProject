#include "Bishop.h"
#include <cmath>

// Constructor: Initializes a Bishop object with a name, color, and position.
// Parameters:
// - name: The character representing the name of the piece.
// - color: The character representing the color of the piece.
// - row: The initial row position of the piece.
// - col: The initial column position of the piece.
Bishop::Bishop(const char name, const char color, const int row, const int col)
    : GamePiece(name, color, row, col) {
}

// Copy Constructor: Creates a new Bishop object by copying another Bishop object.
// Parameters:
// - other: The Bishop object to copy.
Bishop::Bishop(const Bishop& other) : GamePiece(other) {}

// Destructor: Cleans up resources used by the Bishop object.
Bishop::~Bishop() {}

// Checks if the Bishop can move to the specified position.
// Parameters:
// - newRow: The target row to move to.
// - newCol: The target column to move to.
// - board: The game board represented as a 2D array of pointers to GamePiece objects.
// Returns: True if the move is valid for a Bishop, false otherwise.
bool Bishop::canMove(const int newRow, const int newCol, GamePiece* board[BOARD_SIZE][BOARD_SIZE])
{
    int rowDiff = abs(newRow - this->_pos[ROW_INDEX]);
    int colDiff = abs(newCol - this->_pos[COL_INDEX]);

    // A Bishop can only move diagonally, so rowDiff must equal colDiff
    // Check if the path to the target position is clear
    if (rowDiff == colDiff && this->IsPathClear(newRow, newCol, board))
    {
        return true;
    }
    return false;
}

// Creates a copy of the Bishop object.
// Returns: A pointer to a new Bishop object that is a clone of the current object.
GamePiece* Bishop::clone() const
{
    return new Bishop(*this);
}
