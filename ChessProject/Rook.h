#pragma once
#include "GamePiece.h"
class Rook : public GamePiece
{
public:
	Rook(const char name, const char color, const int row, const int col);
	~Rook();
	virtual bool canMove() override;
};

