#include "Board.h"

// Constructor to initialize the board with game pieces based on the placement string
// Input: placement string (a string of characters representing the pieces' positions)
// Output: none
Board::Board(const char placement[PLACEMENT_STRING_SIZE])
{
    int row = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            switch (placement[row + j])
            {
            case whiteGamePieces::whiteRook:
                this->_board[i][j] = new Rook(whiteGamePieces::whiteRook, ChessColors::white, i, j);
                break;
            case blackGamePieces::blackRook:
                this->_board[i][j] = new Rook(blackGamePieces::blackRook, ChessColors::black, i, j);
                break;
            case whiteGamePieces::whiteKing:
                this->_board[i][j] = new King(whiteGamePieces::whiteKing, ChessColors::white, i, j);
                break;
            case blackGamePieces::blackKing:
                this->_board[i][j] = new King(blackGamePieces::blackKing, ChessColors::black, i, j);
                break;
            case whiteGamePieces::whiteKnight:
                this->_board[i][j] = new Knight(whiteGamePieces::whiteKnight, ChessColors::white, i, j);
                break;
            case blackGamePieces::blackKnight:
                this->_board[i][j] = new Knight(blackGamePieces::blackKnight, ChessColors::black, i, j);
                break;
            case whiteGamePieces::whiteBishop:
                this->_board[i][j] = new Bishop(whiteGamePieces::whiteBishop, ChessColors::white, i, j);
                break;
            case blackGamePieces::blackBishop:
                this->_board[i][j] = new Bishop(blackGamePieces::blackBishop, ChessColors::black, i, j);
                break;
            case whiteGamePieces::whiteQueen:
                this->_board[i][j] = new Queen(whiteGamePieces::whiteQueen, ChessColors::white, i, j);
                break;
            case blackGamePieces::blackQueen:
                this->_board[i][j] = new Queen(blackGamePieces::blackQueen, ChessColors::black, i, j);
                break;
            case whiteGamePieces::whitePawn:
                this->_board[i][j] = new Pawn(whiteGamePieces::whitePawn, ChessColors::white, i, j);
                break;
            case blackGamePieces::blackPawn:
                this->_board[i][j] = new Pawn(blackGamePieces::blackPawn, ChessColors::black, i, j);
                break;
            default:
                break;
            }
        }
        row += BOARD_SIZE;
    }
}

// Destructor to clean up dynamically allocated memory for the pieces
// Input: none
// Output: none
Board::~Board()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (this->_board[i][j] != nullptr)
            {
                delete this->_board[i][j];
            }
        }
    }
}

// Function to print the board in a readable format
// Input: none
// Output: prints the board to the console
void Board::printBoard() const {
    // Print column labels
    std::cout << "   ";
    for (int col = 0; col < BOARD_SIZE; ++col) {
        std::cout << (char)('A' + col) << " ";
    }
    std::cout << '\n';

    // Print rows
    for (int row = 0; row < BOARD_SIZE; ++row) {
        std::cout << (row + 1) << "  "; // Row label
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (_board[row][col] != nullptr) {
                std::cout << _board[row][col]->getName() << " "; // Print piece name
            }
            else {
                std::cout << "# "; // Empty cell
            }
        }
        std::cout << '\n';
    }
}

void Board::eat(const int row,const int col)
{
    delete this->_board[row][col];
}

void Board::getPosFromString(const std::string posString, int* pos)
{
    pos[ROW_INDEX] = abs(posString[ROW_INDEX_STRING] - '8');
    pos[COL_INDEX] = abs(posString[COL_INDEX_STRING] - 'a');
}

void Board::movePiece(const int sourceRow, const int sourceCol, const int destRow, const int destCol)
{
    GamePiece* temp = nullptr;
    temp = this->_board[sourceRow][sourceCol];
    this->_board[sourceRow][sourceCol] = nullptr;
    if ((this->_board[destRow][destCol] != nullptr) && (this->_board[destRow][destCol]->getColor() != temp->getColor()))
    {
        eat(destRow, destCol);
    }
    temp->setPieceCol(destCol);
    temp->setPieceRow(destRow);
    this->_board[destRow][destCol] = temp;
}

GamePiece* Board::getGamePiece(const int row, const int col) const
{
    return this->_board[row][col];
}
