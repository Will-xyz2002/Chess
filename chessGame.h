#ifndef CHESS_GAME_H
#define CHESS_GAME_H
#include "chessBoard.h"
#include "chessMove.h"
#include "player.h"
#include <vector>
#include <string>

class ChessGame {
    ChessBoard board;
    bool whiteTurn = true;
    bool isWon = false;
    Player p1;
    Player p2;
    std::vector<ChessMove> moveLog;

public:
    ChessGame(ChessBoard board, bool whiteTurn, Player p1, Player p2);
    bool isWhiteTurn();
    bool gameWon();
    void makeAMove(std::string initial, std::string dest);
    void undo();
    void resign();
};


#endif
