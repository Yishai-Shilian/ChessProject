#include "GamePiece.h"

/*
a constructor for initialization a game piece
input: name, color, row, col
output: none
*/
GamePiece::GamePiece(const char name, const char color, const int row, const int col) : _name(name), _color(color), _pos{ row, col }
{
}

/*
a destructor for game piece
input: none
output: none
*/
GamePiece::~GamePiece() {}

/*
a function that returns game piece's name
input: none
output: game piece name
*/
char GamePiece::getName() const
{
	return this->_name;
}

/*
a function that returns game piece's color
input: none
output: game piece color
*/
char GamePiece::getColor() const
{
	return this->_color;
}

int GamePiece::getPieceRow() const
{
	return this->_pos[ROW_INDEX];
}

int GamePiece::getPieceCol() const
{
	return this->_pos[COL_INDEX];
}



