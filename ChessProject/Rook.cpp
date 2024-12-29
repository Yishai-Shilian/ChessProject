#include "Rook.h"

// Constructor to initialize rook game piece
// Input: name, color, initial pose
// Output: none
Rook::Rook(const char name, const char color, const int row, const int col) : GamePiece(name, color, row, col) {}

// Copy constructor for rook
Rook::Rook(const Rook& other) : GamePiece(other) {} // Copy constructor implementation

// Destructor for rook game piece
// Input: none
// Output: none
Rook::~Rook() {}

// a function that checks if the move we do on the rook is valid
// Input: the dest row and col, the board
// Output: true if the move is valid false if otherwise
bool Rook::canMove(const int newRow, const int newCol, GamePiece* board[BOARD_SIZE][BOARD_SIZE])
{
    if ((this->_pos[ROW_INDEX] == newRow || this->_pos[COL_INDEX] == newCol) && this->IsPathClear(newRow, newCol, board))
    {
        return true;
    }
    return false;
}

// Clone method implementation
GamePiece* Rook::clone() const
{
    return new Rook(*this);
}
