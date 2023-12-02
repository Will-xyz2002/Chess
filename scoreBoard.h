#ifndef SCORE_BOARD
#define SCORE_BOARD

#include <iostream>

class ScoreBoard{
    float white_score = 0.0f;
    float black_score = 0.0f;
public:
    void white_won(); // add one point to white
    void black_won(); // add one point to black
    void add_both(); // add half points to both
    void printScore(); // print it out
};

#endif
