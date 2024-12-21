#include "Queen.h"

Queen::Queen(const char name, const char color, const int row, const int col) : GamePiece(name, color, row, col) 
{
   
}
Queen::~Queen()
{
    
}

bool Queen::canMove(int newRow, int newCol) const
{
    return false;
}
