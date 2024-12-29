#pragma once
#include "GamePiece.h"

#define DOUBLE_STEP_FIRST_MOVE 2

class Pawn : public GamePiece
{
public:
    Pawn(const char name, const char color, const int row, const int col);
    Pawn(const Pawn& other); // Copy constructor
    ~Pawn();
    virtual bool canMove(const int newRow, const int newCol, GamePiece* board[BOARD_SIZE][BOARD_SIZE]) override;
    virtual GamePiece* clone() const override; // Clone method
    int getDir() const;
private:
    bool _isFirstMove;
};
