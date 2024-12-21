#pragma once
#include "GamePiece.h"
class Knight : public GamePiece 
{
public:
	Knight(const char name, const char color, const int row, const int col);
	~Knight();
	virtual bool canMove(int newRow, int newCol) const override;
private:

protected:
	void move();
	void eat();


};