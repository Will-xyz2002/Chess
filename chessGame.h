#ifndef CHESS_GAME_H
#define CHESS_GAME_H
#include "chessBoard.h"
#include "chessMove.h"
#include "textDisplay.h"
#include "graphicsdisplay.h"
#include "player.h"
#include <vector>
#include <string>

class ChessGame {
    ChessBoard board;
    std::unique_ptr<TextDisplay> textDisplay;
    std::unique_ptr<GraphicsDisplay> graphicsDisplay;
    bool whiteTurn = true;
    bool isWhiteWin = false;
    bool isStalemate = false;
    bool isWon = false;
    std::shared_ptr<Player> whitePlayer;
    std::shared_ptr<Player> blackPlayer;
    std::vector<ChessMove> moveLog;

    void nextTurn();
    void movePiece(ChessSquare source, ChessSquare destination);

public:
    ChessGame(ChessBoard board, bool whiteTurn, std::shared_ptr<Player> whitePlayer, std::shared_ptr<Player> blackPlayer);
    bool isWhiteTurn();
    bool isStalemated();
    bool gameWon();
    void makeAMove(std::string initial, std::string dest); // for human player
    void makeAMove();                                      // for computer player
    void undo();
    void resign();
    vector<ChessMove> getAllMoves();
    vector<ChessMove> getCaptureMoves();
    vector<ChessMove> getCheckMoves();
};

#endif
