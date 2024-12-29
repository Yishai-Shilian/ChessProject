#include "Chess.h"
#include <string>

// Constructor: Initializes a Chess object with the starting board and sets the current player to white.
Chess::Chess() : _board(STARTING_STRING), _currPlayer(ChessColors::white) {}

// Destructor: Cleans up resources used by the Chess object.
Chess::~Chess() {}

// Main game loop to handle the chess game logic.
void Chess::play()
{
    char msgToGraphics[MSG_SIZE];
    bool isConnect = this->_pipe.connect();
    std::string ans;

    while (!isConnect)
    {
        std::cout << "Cannot connect to graphics" << std::endl;
        std::cout << "Do you want to try again or exit? (0 - Try again, 1 - Exit)" << std::endl;
        std::cin >> ans;

        if (ans == "0")
        {
            std::cout << "Trying to connect again..." << std::endl;
            Sleep(5000);
            isConnect = this->_pipe.connect();
        }
        else
        {
            this->_pipe.close();
            return;
        }
    }

    strcpy_s(msgToGraphics, STARTING_STRING);
    this->_pipe.sendMessageToGraphics(msgToGraphics);

    this->_board.printBoard();

    std::string msgFromGraphics = this->_pipe.getMessageFromGraphics();

    while (msgFromGraphics != "quit")
    {
        int sourcePose[2];
        Board::getPosFromString(msgFromGraphics.substr(0, SIZE_POS), sourcePose);
        int destPose[2];
        Board::getPosFromString(msgFromGraphics.substr(SIZE_POS, SIZE_POS + SIZE_POS), destPose);

        int frontendCode = this->CheckCode(this->_currPlayer, this->_board._board, sourcePose, destPose);
        msgToGraphics[0] = (char)(frontendCode + CHAR_TO_NUM_CONVERTOR);
        msgToGraphics[1] = 0;
        this->_pipe.sendMessageToGraphics(msgToGraphics);

        this->_board.printBoard();
        if (frontendCode == FrontendCodes::vaildMove || frontendCode == FrontendCodes::validMoveCausesChessRival)
        {
            this->switchTurns();
        }

        msgFromGraphics = this->_pipe.getMessageFromGraphics();
    }

    this->_pipe.close();
}

// Switches the turn to the other player.
void Chess::switchTurns()
{
    if (this->_currPlayer == ChessColors::black)
    {
        this->_currPlayer = ChessColors::white;
    }
    else
    {
        this->_currPlayer = ChessColors::black;
    }
}

// Checks if a move causes the opponent's king to be in check.
// Parameters:
// - currPlayer: The current player's color.
// - srcPos: The source position of the move.
// - dstPos: The destination position of the move.
// - board: The current board state.
// Returns:
// - FrontendCodes::validMoveCausesChessRival if the move causes a check on the rival.
bool Chess::checkCode1(const ChessColors currPlayer, const int* srcPos, const int* dstPos, GamePiece* board[BOARD_SIZE][BOARD_SIZE])
{
    return madeChess(getOpponentColor(), srcPos, dstPos, board);
}

// Checks if the source square has no piece or if the piece does not belong to the current player.
// Parameters:
// - board: The current board state.
// - srcPos: The source position.
// Returns:
// - true if the source square is invalid, false otherwise.
bool Chess::checkCode2(GamePiece* board[BOARD_SIZE][BOARD_SIZE], const int* srcPos)
{
    if (board[srcPos[ROW_INDEX]][srcPos[COL_INDEX]] == nullptr || board[srcPos[ROW_INDEX]][srcPos[COL_INDEX]]->getColor() != this->_currPlayer)
    {
        return true;
    }
    return false;
}


// Checks if the destination square contains a piece of the current player.
// Parameters:
// - board: The current board state.
// - dstPos: The destination position.
// Returns:
// - true if the destination square is occupied by a piece of the current player, false otherwise.
bool Chess::checkCode3(GamePiece* board[BOARD_SIZE][BOARD_SIZE], const int* dstPos)
{
    if (board[dstPos[ROW_INDEX]][dstPos[COL_INDEX]] != nullptr &&
        board[dstPos[ROW_INDEX]][dstPos[COL_INDEX]]->getColor() == this->_currPlayer)
    {
        return true;
    }
    return false;
}

// Checks if the move would result in a check for the current player's king.
// Parameters:
// - currPlayer: The current player's color.
// - srcPos: The source position of the move.
// - dstPos: The destination position of the move.
// - board: The current board state.
// Returns:
// - true if the move causes a check for the current player's king, false otherwise.
bool Chess::checkCode4(const ChessColors currPlayer, const int* srcPos, const int* dstPos, GamePiece* board[BOARD_SIZE][BOARD_SIZE])
{
    return madeChess(currPlayer, srcPos, dstPos, board);
}

// Checks if the source or destination indices are out of bounds.
// Parameters:
// - dstPos: The destination position.
// - srcPos: The source position.
// Returns:
// - true if the indices are out of bounds, false otherwise.
bool Chess::checkCode5(const int* dstPos, const int* srcPos)
{
    if (dstPos[ROW_INDEX] < 0 || dstPos[ROW_INDEX] >= BOARD_SIZE ||
        dstPos[COL_INDEX] < 0 || dstPos[COL_INDEX] >= BOARD_SIZE)
    {
        return true;
    }

    if (srcPos[ROW_INDEX] < 0 || srcPos[ROW_INDEX] >= BOARD_SIZE ||
        srcPos[COL_INDEX] < 0 || srcPos[COL_INDEX] >= BOARD_SIZE)
    {
        return true;
    }

    return false;
}
// Checks if the piece at the source position can move to the destination position.
// Parameters:
// - board: The current board state.
// - srcPos: The source position.
// - dstPos: The destination position.
// Returns:
// - true if the piece cannot move to the destination, false otherwise.
bool Chess::checkCode6(GamePiece* board[BOARD_SIZE][BOARD_SIZE], const int* srcPos, const int* dstPos)
{
    if (!board[srcPos[ROW_INDEX]][srcPos[COL_INDEX]]->canMove(dstPos[ROW_INDEX], dstPos[COL_INDEX], board))
    {
        return true;
    }
    return false;
}


// Checks if the source and destination positions are identical.
// Parameters:
// - dstPos: The destination position.
// - srcPos: The source position.
// Returns:
// - true if the positions are identical, false otherwise.
bool Chess::checkCode7(const int* dstPos, const int* srcPos)
{
    if (dstPos[ROW_INDEX] == srcPos[ROW_INDEX] && dstPos[COL_INDEX] == srcPos[COL_INDEX])
    {
        return true;
    }
    return false;
}

// Checks the validity of a move and returns an appropriate frontend code.
// Parameters:
// - currPlayer: The current player's color.
// - board: The current board state.
// - srcPos: The source position.
// - dstPos: The destination position.
// Returns:
// - Frontend code corresponding to the move's validity.
int Chess::CheckCode(const ChessColors currPlayer, GamePiece* board[BOARD_SIZE][BOARD_SIZE], const int* srcPos, const int* dstPos)
{
    if (checkCode2(board, srcPos)) {
        return FrontendCodes::sourceSquareNoCurrPiece;
    }
    else if (checkCode3(board, dstPos))
    {
        return FrontendCodes::destSquareHaveCurrPiece;
    }
    else if (checkCode4(currPlayer, srcPos, dstPos, board))
    {
        return FrontendCodes::moveCauseChessCurrPlayer;
    }
    else if (checkCode5(dstPos, srcPos))
    {
        return FrontendCodes::illegalIndex;
    }
    else if (checkCode6(board, srcPos, dstPos))
    {
        return FrontendCodes::illegalPieceMove;
    }
    else if (checkCode7(dstPos, srcPos))
    {
        return FrontendCodes::sourceDestSquareIdentical;
    }
    else if (checkCode1(this->_currPlayer, srcPos, dstPos, this->_board._board))
    {
        this->_board.movePiece(srcPos[ROW_INDEX], srcPos[COL_INDEX], dstPos[ROW_INDEX], dstPos[COL_INDEX]);
        return FrontendCodes::validMoveCausesChessRival;
    }
    this->_board.movePiece(srcPos[ROW_INDEX], srcPos[COL_INDEX], dstPos[ROW_INDEX], dstPos[COL_INDEX]);
    return FrontendCodes::vaildMove;
}
// Gets the opponent player's color.
// Returns:
// - The color of the opponent player.
ChessColors Chess::getOpponentColor() const
{
    if (this->_currPlayer == ChessColors::black)
    {
        return ChessColors::white;
    }
    return ChessColors::black;
}

// Simulates a move and checks if it results in a check.
// Parameters:
// - currPlayer: The current player's color.
// - srcPos: The source position.
// - dstPos: The destination position.
// - board: The current board state.
// Returns:
// - true if the move results in a check, false otherwise.
bool Chess::madeChess(const ChessColors currPlayer, const int* srcPos, const int* dstPos, GamePiece* board[BOARD_SIZE][BOARD_SIZE])
{
    bool isChess = false;
    int kingPos[SIZE_POS];
    GamePiece* movingPiece = nullptr;
    GamePiece* capturedPiece = nullptr;

    movingPiece = board[srcPos[ROW_INDEX]][srcPos[COL_INDEX]];
    if (movingPiece == nullptr)
    {
        return false;
    }

    GamePiece* copiedPiece = movingPiece->clone();

    capturedPiece = board[dstPos[ROW_INDEX]][dstPos[COL_INDEX]];
    board[dstPos[ROW_INDEX]][dstPos[COL_INDEX]] = movingPiece;
    board[srcPos[ROW_INDEX]][srcPos[COL_INDEX]] = nullptr;

    movingPiece->setPieceRow(dstPos[ROW_INDEX]);
    movingPiece->setPieceCol(dstPos[COL_INDEX]);

    getPosKing(currPlayer, kingPos);

    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            GamePiece* opponentPiece = board[i][j];
            if (opponentPiece != nullptr && opponentPiece->getColor() != currPlayer)
            {
                if (opponentPiece->canMove(kingPos[ROW_INDEX], kingPos[COL_INDEX], board))
                {
                    isChess = true;
                    break;
                }
            }
        }
        if (isChess)
        {
            break;
        }
    }

    delete movingPiece;

    board[srcPos[ROW_INDEX]][srcPos[COL_INDEX]] = copiedPiece;
    board[dstPos[ROW_INDEX]][dstPos[COL_INDEX]] = capturedPiece;

    copiedPiece->setPieceRow(srcPos[ROW_INDEX]);
    copiedPiece->setPieceCol(srcPos[COL_INDEX]);

    return isChess;
}
// Gets the position of the king of a specific color.
// Parameters:
// - kingColor: The color of the king.
// - pos: An array to store the king's position (row, column).
void Chess::getPosKing(const ChessColors kingColor, int* pos)
{
    bool found = false;
    for (int i = 0; i < BOARD_SIZE && !found; i++)
    {
        for (int j = 0; j < BOARD_SIZE && !found; j++)
        {
            if (this->_board._board[i][j] != nullptr)
            {
                if (this->_board._board[i][j]->getColor() == kingColor &&
                    toupper(this->_board._board[i][j]->getName()) == 'K')
                {
                    pos[ROW_INDEX] = i;
                    pos[COL_INDEX] = j;
                    found = true;
                }
            }
        }
    }
}
