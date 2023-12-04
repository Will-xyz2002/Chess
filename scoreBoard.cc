#include "scoreBoard.h"
using namespace std;

void ScoreBoard::white_won(){
    white_score = white_score + 1.0f;
}

void ScoreBoard::black_won(){
    black_score = black_score + 1.0f;
}

void ScoreBoard::add_both(){
    white_score = white_score + 0.5f;
    black_score = black_score + 0.5f;
}

void ScoreBoard::printScore(){
    cout << "Final Score:" << endl;
    cout << "White: " << white_score << endl;
    cout << "Black: " << black_score << endl;
}

void ScoreBoard::reset(){
    white_score = 0.0f;
    black_score = 0.0f;
}
