#pragma once
#pragma once
#include "GamePiece.h"

class Pawn : public GamePiece
{
public:
    Pawn(const char name, const char color, const int row, const int col);
    ~Pawn();
    virtual bool canMove(int newRow, int newCol) const override;
    bool isFirstMove() const;
private:
    bool _isFirstMove;
};
