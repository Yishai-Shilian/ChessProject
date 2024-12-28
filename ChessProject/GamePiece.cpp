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

void GamePiece::setPieceRow(const int newRow)
{
	this->_pos[ROW_INDEX] = newRow;
}

void GamePiece::setPieceCol(const int newCol)
{
	this->_pos[COL_INDEX] = newCol;
}

bool GamePiece::IsPathClear(const int newRow, const int newCol, GamePiece* board[BOARD_SIZE][BOARD_SIZE]) {
    // Current position
    int currentRow = this->_pos[ROW_INDEX];
    int currentCol = this->_pos[COL_INDEX];

    // Check if the piece is a Rook or Queen
    if (std::toupper(this->getName()) == 'R' || std::toupper(this->getName()) == 'Q') {
        // Movement is along a straight line: either row or column changes
        if (currentRow == newRow) {
            // Horizontal movement
            int colStep;
            if (newCol > currentCol) {
                colStep = 1; // Moving right
            }
            else {
                colStep = -1; // Moving left
            }

            for (int col = currentCol + colStep; col != newCol; col += colStep) {
                if (board[currentRow][col] != nullptr) {
                    return false; // Path is blocked
                }
            }
        }
        else if (currentCol == newCol) {
            // Vertical movement
            int rowStep;
            if (newRow > currentRow) {
                rowStep = 1; // Moving down
            }
            else {
                rowStep = -1; // Moving up
            }

            for (int row = currentRow + rowStep; row != newRow; row += rowStep) {
                if (board[row][currentCol] != nullptr) {
                    return false; // Path is blocked
                }
            }
        }
    }

    // Check for diagonal paths (for Queen only)
    if (std::toupper(this->getName()) == 'Q' || std::toupper(this->getName()) == 'B') {
        if (std::abs(newRow - currentRow) == std::abs(newCol - currentCol)) {
            // Diagonal movement
            int rowStep;
            if (newRow > currentRow) {
                rowStep = 1; // Moving down
            }
            else {
                rowStep = -1; // Moving up
            }

            int colStep;
            if (newCol > currentCol) {
                colStep = 1; // Moving right
            }
            else {
                colStep = -1; // Moving left
            }

            int row = currentRow + rowStep;
            int col = currentCol + colStep;
            while (row != newRow && col != newCol) {
                if (board[row][col] != nullptr) {
                    return false; // Path is blocked
                }
                row += rowStep;
                col += colStep;
            }
        }
    }

    return true; // Path is clear
}
