#include "GamePiece.h"
#include "GamePiece.h"

// Constructor: Initializes a GamePiece object with a name, color, and position.
// Parameters:
// - name: The character representing the name of the piece.
// - color: The character representing the color of the piece.
// - row: The initial row position of the piece.
// - col: The initial column position of the piece.
GamePiece::GamePiece(const char name, const char color, const int row, const int col)
    : _name(name), _color(color), _pos{ row, col }
{
}

// Copy Constructor: Creates a new GamePiece object by copying another GamePiece.
// Parameters:
// - other: The GamePiece object to copy.
GamePiece::GamePiece(const GamePiece& other)
    : _name(other._name), _color(other._color)
{
    _pos[ROW_INDEX] = other._pos[ROW_INDEX];
    _pos[COL_INDEX] = other._pos[COL_INDEX];
}

// Destructor: Cleans up resources used by the GamePiece object.
GamePiece::~GamePiece() {}

// Returns the name of the game piece.
// Returns: The name character of the piece.
char GamePiece::getName() const
{
    return this->_name;
}

// Returns the color of the game piece.
// Returns: The color character of the piece.
char GamePiece::getColor() const
{
    return this->_color;
}

// Updates the row position of the game piece.
// Parameters:
// - newRow: The new row to set for the piece.
void GamePiece::setPieceRow(const int newRow)
{
    this->_pos[ROW_INDEX] = newRow;
}

// Updates the column position of the game piece.
// Parameters:
// - newCol: The new column to set for the piece.
void GamePiece::setPieceCol(const int newCol)
{
    this->_pos[COL_INDEX] = newCol;
}

// Checks if the path to the specified position is clear for movement.
// Parameters:
// - newRow: The target row to move to.
// - newCol: The target column to move to.
// - board: The game board represented as a 2D array of pointers to GamePiece objects.
// Returns: True if the path is clear, false otherwise.
bool GamePiece::IsPathClear(const int newRow, const int newCol, GamePiece* board[BOARD_SIZE][BOARD_SIZE]) {
    int currentRow = this->_pos[ROW_INDEX];
    int currentCol = this->_pos[COL_INDEX];

    if (std::toupper(this->getName()) == 'R' || std::toupper(this->getName()) == 'Q') {

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
                    return false;
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
                    return false;
                }
            }
        }
    }

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
                    return false;
                }
                row += rowStep;
                col += colStep;
            }
        }
    }

    return true;
}
