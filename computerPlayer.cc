#include "computerPlayer.h"
#include <cstdlib> 

ComputerPlayer::ComputerPlayer(ChessColour colour, int level): Player{colour}, level{level} { }

bool ComputerPlayer::isHuman(){
    return false;
}

ChessMove ComputerPlayer::generateMove(ChessBoard &board) {
    std::vector<ChessMove> allPossibleMoves = board.PossibleMoveGenerator(getColour());
    int size = allPossibleMoves.size();
    if (level >= 2) {
        std::vector<ChessMove> allCapturingMoves;
        for (int i = 0; i < size; ++i) {
            if (board.isChecking(allPossibleMoves[i]) || board.isCapturing(allPossibleMoves[i])) {
                allCapturingMoves.emplace_back(allPossibleMoves[i]);
            }
            int numberOfCapturingMoves = allCapturingMoves.size();
            if (numberOfCapturingMoves != 0) {
                int index = rand() % numberOfCapturingMoves;
                return allCapturingMoves[index];
            }
        }
    }
    int index = rand() % size;
    return allPossibleMoves[index];
}
