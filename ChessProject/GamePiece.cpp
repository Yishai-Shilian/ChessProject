#include "GamePiece.h"

/*
a constructor for initialization a game piece
input: name, color, row, col
output: none
*/
GamePiece::GamePiece(const std::string name, const std::string color, const int row, const int col) : _name(name),
_color(color), _pos{ row, col }
{}

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
std::string GamePiece::getName() const
{
	return this->_name;
}

/*
a function that returns game piece's color
input: none
output: game piece color
*/
std::string GamePiece::getColor() const
{
	return this->_color;
}