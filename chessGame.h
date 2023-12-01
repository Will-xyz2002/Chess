#ifndef CHESS_GAME_H
#define CHESS_GAME_H
#include "chessBoard.h"
#include "chessMove.h"
#include "player.h"
#include <vector>
#include <string>

class ChessGame {
    ChessBoard board;
    TextDisplay textDisplay;
    bool whiteTurn = true;
    bool isWhiteWin = false;
    bool isStalemate = false;
    bool isWon = false;
    Player p1;
    Player p2;
    std::vector<ChessMove> moveLog;

public:
    ChessGame(ChessBoard board, bool whiteTurn, Player p1, Player p2);
    bool isWhiteTurn();
    bool gameWon();
    void makeAMove(std::string initial, std::string dest); // for human player
    void makeAMove();                                      // for computer player
    void undo();
    void resign();
};

#endif
