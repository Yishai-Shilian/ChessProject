#pragma once
#include <iostream>
#define SIZE_POS 2
#define ROW_INDEX 0
#define COL_INDEX 1
class GamePiece
{
public:
	GamePiece(const char name, const char color, const int row, const int col);
	virtual ~GamePiece();
	virtual void eat() = 0; //maybey
	virtual void move() = 0; //maybey
	char getName() const;
	char getColor() const;
	//maybey return to pos (getter to pos)

private:
	char _name;
	char _color;
	int _pos[SIZE_POS];
};
