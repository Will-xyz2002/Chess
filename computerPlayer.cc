#include "computerPlayer.h"

ComputerPlayer::ComputerPlayer(ChessColour colour, int level): Player{colour}, level{level} { }

bool ComputerPlayer::isHuman(){
    return false;
}

ChessMove ComputerPlayer::generateMove(vector<ChessMove> pool){
    int randomIndex = rand() % pool.size();
    ChessMove result = pool[randomIndex];
    return result;
}
