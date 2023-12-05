#include "player.h"

using namespace std;

Player::Player(ChessColour colour): colour{colour} {}
ChessColour Player::getColour() { return colour; }
