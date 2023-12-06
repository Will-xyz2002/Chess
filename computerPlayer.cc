#include "computerPlayer.h"
#include <cstdlib> 
#include <ctime>

ComputerPlayer::ComputerPlayer(ChessColour colour, int level): Player{colour}, level{level} { }

bool ComputerPlayer::isHuman(){
    return false;
}

ChessMove ComputerPlayer::generateMove(ChessBoard &board) {
    srand(time(NULL));
    std::vector<ChessMove> allPossibleMoves = board.PossibleMoveGenerator(getColour());
    std::vector<ChessPiece> alldangeroursPiece = board.getUnderAttackPieces(getColour());
    std::vector<ChessMove> allCapturingMoves;
    int danger_length = alldangeroursPiece.size();
    int size = allPossibleMoves.size();
    if (level == 2) {
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
    if (level == 3){
        std::vector<ChessMove> avoidingMove;
        // do level_2 first
        for (int i = 0; i < size; ++i) {
                if (board.isChecking(allPossibleMoves[i]) || board.isCapturing(allPossibleMoves[i])) {
                    allCapturingMoves.emplace_back(allPossibleMoves[i]);
                }
        }
        int numberOfCapturingMoves = allCapturingMoves.size();
        if (danger_length == 0){
            if (numberOfCapturingMoves == 0){
                int random = rand() % size;
                return allPossibleMoves[random];
            }
            else{
                int random = rand() % numberOfCapturingMoves;
                return allCapturingMoves[random];
            }
        }
        // danger_length is not zero
        int under_attack_index = rand() % danger_length;
        avoidingMove = board.avoidAttackGenerator(alldangeroursPiece[under_attack_index]);
        std::copy(allCapturingMoves.begin(), allCapturingMoves.end(), std::back_inserter(avoidingMove));
        // now the avoidingmoves has all the avoiding move and capturing move
        int final_index = rand() % avoidingMove.size();
        return avoidingMove[final_index];
    }
    if (level == 4){
        std::vector<ChessMove> bestMoves;
        int bestSoFar = -20;
        for(int i = 0; i < size; ++i) {
            int currentPoint = board.getplayPoint(allPossibleMoves[i]);
            if(bestSoFar == currentPoint) {
                bestMoves.emplace_back(allPossibleMoves[i]);
            } else if(bestSoFar <  currentPoint) {
                bestMoves.clear();
                bestMoves.emplace_back(allPossibleMoves[i]);
                bestSoFar = currentPoint;
            }
        }
        int numberOfBestMoves = bestMoves.size();
        int final_index = rand() % numberOfBestMoves;
        return bestMoves[final_index];
    }
    int index = rand() % size;
    return allPossibleMoves[index];
}
