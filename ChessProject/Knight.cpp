#include "Knight.h"
#include <cmath>

// Constructor: Initializes a Knight object with a name, color, and position.
// Parameters:
// - name: The character representing the name of the piece.
// - color: The character representing the color of the piece.
// - row: The initial row position of the piece.
// - col: The initial column position of the piece.
Knight::Knight(const char name, const char color, const int row, const int col)
    : GamePiece(name, color, row, col) {
}

// Copy Constructor: Creates a new Knight object by copying another Knight object.
// Parameters:
// - other: The Knight object to copy.
Knight::Knight(const Knight& other) : GamePiece(other) {}

// Destructor: Cleans up resources used by the Knight object.
Knight::~Knight() {}

// Checks if the Knight can move to the specified position.
// Parameters:
// - newRow: The target row to move to.
// - newCol: The target column to move to.
// - board: The game board represented as a 2D array of pointers to GamePiece objects.
// Returns: True if the move is valid for a Knight, false otherwise.
bool Knight::canMove(const int newRow, const int newCol, GamePiece* board[BOARD_SIZE][BOARD_SIZE])
{
    int rowDiff = abs(newRow - this->_pos[ROW_INDEX]);
    int colDiff = abs(newCol - this->_pos[COL_INDEX]);
    if ((rowDiff == diffCubes::two && colDiff == diffCubes::one)
        || (rowDiff == diffCubes::one && colDiff == diffCubes::two))
    {
        return true;
    }
    return false;
}

// Creates a copy of the Knight object.
// Returns: A pointer to a new Knight object that is a clone of the current object.
GamePiece* Knight::clone() const
{
    return new Knight(*this);
}
