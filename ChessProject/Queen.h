#pragma once
#pragma once
#include "GamePiece.h"

class Queen : public Rook,Bishop
{
public:
    Queen(const char name, const char color, const int row, const int col);
    ~Queen();
    virtual bool canMove(int newRow, int newCol) const override;    

private:
};
