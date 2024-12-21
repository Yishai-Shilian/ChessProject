#pragma once
#include "GamePiece.h"
class King : public  GamePiece
{
public:
	King(const char name, const char color, const int row, const int col);
	~King();
	virtual bool canMove(int newRow,int newCul) const override;
private:
	void move();
};

