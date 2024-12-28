#pragma once
#include "GamePiece.h"

class Pawn : public GamePiece
{
public:

    Pawn(const char name, const char color, const int row, const int col);
    ~Pawn();
    virtual bool canMove(const int newRow, const int newCol, GamePiece* board[BOARD_SIZE][BOARD_SIZE]) override;
    int getDir()const;
private:
    bool _isFirstMove; 
};
