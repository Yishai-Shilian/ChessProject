#include "Pawn.h"
#include <cmath> // For abs()
#include "ChessEnums.h"
Pawn::Pawn(const char name, const char color, const int row, const int col)
    : GamePiece(name, color, row, col), _isFirstMove(true)
{
}

Pawn::~Pawn()
{
}

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
    
    //if first move
    if (this->_isFirstMove == false)
    {
        //check coldiff and rowdiff for basic movement
        if (colDiff == 0 && rowDiff == 1 && board[newRow][newCol] == nullptr)
        {
            return true;
        }
        //eating thing if the row diffrance is 1 and only when there is sombody there and the color is diffrant
        if (abs(rowDiff) == 1 && abs(colDiff) == 1 && board[newRow][newCol] != nullptr && board[newRow][newCol]->getColor() != this->getColor())
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
        if (rowDiff == 2 && colDiff == 0 && board[newRow + getDir()][newCol] == nullptr && board[newRow][newCol] == nullptr)
        {
            this->_isFirstMove = false;
            return true;
        }
        if (abs(rowDiff) == 1 && abs(colDiff) == 1 && board[newRow][newCol] != nullptr && board[newRow][newCol]->getColor() != this->getColor())
        {
            this->_isFirstMove = false;
            return true;
        }
    }
    return false;
}

int Pawn::getDir() const
{
    if (this->getColor() == ChessColors::white)
    {
        return 1;
    }
    return -1;
}
