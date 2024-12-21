#include "Knight.h"

Knight::Knight(const char name, const char color, const int row, const int col) : GamePiece(name, color, row, col) 
{
}

Knight::~Knight()
{
    
}

bool Knight::canMove(int newRow, int newCol) const
{
    return false;
}
