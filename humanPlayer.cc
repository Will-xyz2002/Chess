#include "humanPlayer.h"
#include "empty.h"

HumanPlayer::HumanPlayer(ChessColour colour): Player{colour} { }

bool HumanPlayer::isHuman(){
    return true;
}

ChessMove HumanPlayer::generateMove(ChessBoard &board) { 
    ChessPiece dummy1 = Empty {{0, 0}};
    ChessPiece dummy2 = Empty {{0, 0}};
    return {dummy1, dummy2};
}
