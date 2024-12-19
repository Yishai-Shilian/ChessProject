#pragma once
#include <iostream>
#define SIZE_POS 2
#define ROW_INDEX 0
#define COL_INDEX 1
class GamePiece
{
public:
	GamePiece(const std::string name, const std::string color, const int row, const int col);
	virtual ~GamePiece();
	virtual void eat() = 0;
	virtual void move() = 0;
	std::string getName() const;
	std::string getColor() const;
	//maybey return to pos (getter to pos)

private:
	std::string _name;
	std::string _color;
	int _pos[SIZE_POS];
};
