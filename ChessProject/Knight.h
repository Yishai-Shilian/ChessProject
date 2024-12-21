#pragma once
#include "GamePiece.h"
class Knight : GamePiece 
{
public:
	Knight  ();
	~Knight  ();

private:
	char _name;
	int pos[SIZE_POS];
	char color;
protected:
	void move();
	void eat();


};