#include "computerPlayer.h"

ComputerPlayer::ComputerPlayer(ChessColour colour, int level): Player{colour}, level{level} { }

bool ComputerPlayer::isHuman(){
    return false;
}
