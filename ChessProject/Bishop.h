#pragma once
#include "GamePiece.h"
class Bishop : public GamePiece
{
public:
	Bishop(const char name, const char color, const int row, const int col);
	~Bishop();
	virtual bool canMove(int newRow,int newCul) const override;
private:

};
