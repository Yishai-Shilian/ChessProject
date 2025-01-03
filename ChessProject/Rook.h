#pragma once
#include "GamePiece.h"
#include "Board.h"
class Board;

class Rook : public GamePiece
{
public:
    Rook(const char name, const char color, const int row, const int col);
    Rook(const Rook& other); // Copy constructor
    ~Rook();
    virtual bool canMove(const int newRow, const int newCol, GamePiece* board[BOARD_SIZE][BOARD_SIZE]) override;
    virtual GamePiece* clone() const override; // Clone method
};