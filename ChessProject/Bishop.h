#pragma once
#include "GamePiece.h"
class Bishop : public GamePiece
{
public:
    Bishop(const char name, const char color, const int row, const int col);
    Bishop(const Bishop& other); // Copy constructor
    ~Bishop();
    virtual bool canMove(const int newRow, const int newCol, GamePiece* board[BOARD_SIZE][BOARD_SIZE]) override;
    virtual GamePiece* clone() const override; // Clone method
private:
};