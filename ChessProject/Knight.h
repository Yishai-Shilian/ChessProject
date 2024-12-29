#pragma once
#include "GamePiece.h"

enum diffCubes
{
    one = 1,
    two
};

class Knight : public GamePiece
{
public:
    Knight(const char name, const char color, const int row, const int col);
    Knight(const Knight& other); // Copy constructor
    ~Knight();
    virtual bool canMove(const int newRow, const int newCol, GamePiece* board[BOARD_SIZE][BOARD_SIZE]) override;
    virtual GamePiece* clone() const override;
private:
};
