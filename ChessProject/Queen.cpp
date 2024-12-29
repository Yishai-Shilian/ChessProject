#include "Queen.h"
#include <cmath>

Queen::Queen(const char name, const char color, const int row, const int col) : GamePiece(name, color, row, col) {}

Queen::Queen(const Queen& other) : GamePiece(other) {}

Queen::~Queen() {}

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

GamePiece* Queen::clone() const
{
    return new Queen(*this);
}
