#include "humanPlayer.h"

HumanPlayer::HumanPlayer(ChessColour colour): Player{colour} { }

bool HumanPlayer::isHuman(){
    return true;
}

