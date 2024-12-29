#include "Bishop.h"
#include <cmath>

Bishop::Bishop(const char name, const char color, const int row, const int col) : GamePiece(name, color, row, col) {}

Bishop::Bishop(const Bishop& other) : GamePiece(other) {}

Bishop::~Bishop() {}

bool Bishop::canMove(const int newRow, const int newCol, GamePiece* board[BOARD_SIZE][BOARD_SIZE])
{
    int rowDiff = abs(newRow - this->_pos[ROW_INDEX]);
    int colDiff = abs(newCol - this->_pos[COL_INDEX]);

    if (rowDiff == colDiff && this->IsPathClear(newRow, newCol, board))
    {
        return true;
    }
    return false;
}

GamePiece* Bishop::clone() const
{
    return new Bishop(*this);
}
