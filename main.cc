#include "chessGame.h"
#include "chessBoard.h"
#include "humanPlayer.h"
#include "computerPlayer.h"
#include "scoreBoard.h"
#include "window.h"
#include <iostream>
#include <string>
#include <memory>

using namespace std;


enum class Command {GAME, MOVE, RESIGN, SETUP, ADD_PIECE, REMOVE_PIECE, CHANGE_PLAYER, DONE, NONE};

Command convertCommand(string command) {
    if (command == "game" || command == "g") return Command::GAME;
    if (command == "move" || command == "m") return Command::MOVE;
    if (command == "resign" || command == "r") return Command::RESIGN;
    if (command == "setup" || command == "s") return Command::SETUP;
    if (command == "+") return Command::ADD_PIECE;
    if (command == "-") return Command::REMOVE_PIECE;
    if (command == "done" || command == "d") return Command::DONE;
    if (command == "=") return Command::CHANGE_PLAYER;
    return Command::NONE;
}


bool assignPlayer(string p, unique_ptr<Player> &player, ChessColour colour) {
    if (p == "human" || p == "h") {
        player = make_unique<HumanPlayer>(colour);
        return true;
    }
    else if (p == "computer[1]" || p == "c1") {
        player = make_unique<ComputerPlayer>(colour, 1);
        return true;
    }
    else if (p == "computer[2]" || p == "c2") {
        player = make_unique<ComputerPlayer>(colour, 2);
        return true;
    }
    else if (p == "computer[3]" || p == "c3") {
        player = make_unique<ComputerPlayer>(colour, 3);
        return true;
    }
    return false;
}


int main(void) {
    string command;
    unique_ptr <ChessGame> game = nullptr;
    unique_ptr <ScoreBoard> score = make_unique<ScoreBoard>();
    ChessBoard board;
    bool isWhiteTurn = true;
    bool gameIsOn = false;
    bool setup = false;

    while (cin >> command) {
        switch (convertCommand(command)) {
            case Command::GAME: { // create a new game
                string player1;
                string player2;
                if (cin >> player1 && cin >> player2) {
                    unique_ptr<Player> p1;
                    unique_ptr<Player> p2;
                    if (!assignPlayer(player1, p1, ChessColour::White)) {
                        cout << "Cannot assign white player. Please try again" << endl;
                        break;
                    }
                    if (!assignPlayer(player2, p2, ChessColour::Black)) {
                        cout << "Cannot assign black player. Please try again" << endl;
                        break;
                    }
                    if (!setup) {
                        board.init();
                    }
                    if (game != nullptr) game.reset();
                    game = make_unique<ChessGame>(board, isWhiteTurn, *p1, *p2);
                    board.init();
                    gameIsOn = true;
                }
                break;
            }
            case Command::MOVE: { // player move piece
                if (!gameIsOn) {
                    cout << "No game exist. Please try again" << endl;
                    break;
                }
                string initial;
                string dest;
                if (cin >> initial && cin >> dest) {
                    game->makeAMove(initial, dest);
                }
                if (game->gameWon()) {
                    if(game->isStalemated()){
                        score->add_both();
                    }
                    else if(!game->isWhiteTurn()){
                        // game done by a checkmate, when the colour has the turn lost
                        score->white_won();
                    }
                    else{
                        score->black_won();
                    }
                    board.emptyBoard();
                    isWhiteTurn = true;
                    setup = false;
                    gameIsOn = false;
                }
                break;
            }
            case Command::RESIGN: { // game resign
                if (gameIsOn) {
                    // who resign has the turn
                    if(game->isWhiteTurn()){
                        // white lost
                        score->black_won();
                    }
                    else{
                        score->white_won();
                    }
                    game->resign();
                    gameIsOn = false;
                }
                break;
            }
            case Command::SETUP: { // setting up the board
                setup = true;
                bool setUpComplete = false;
                cout << "Currently on setup mode" << endl;
                cout << board;
                while (cin >> command) {
                    switch (convertCommand(command)) {
                        case Command::ADD_PIECE: { // add a piece to the board
                            char pieceType;
                            string position;
                            if (cin >> pieceType && cin >> position) {
                                board.addPiece(pieceType, position);
                                cout << board;
                            }
                            break;
                        }
                        case Command::REMOVE_PIECE: { // remove a piece from the board
                            string position;
                            if (cin >> position) board.removePiece(position);
                            cout << board;
                            break;
                        }
                        case Command::CHANGE_PLAYER: { // change player
                            string colour;
                            if (cin >> colour) {
                                if (colour == "white") isWhiteTurn = true;
                                else if (colour == "black") isWhiteTurn = false;
                            }
                            break;
                        }
                        case Command::DONE: { // leave setup mode
                            if (board.isValidBoard()) {
                                setUpComplete = true;
                                break;
                            } else {
                                cout << "The board is invalid. Please change your configurations." << endl;
                            }
                            break;
                        }
                        default: {
                            cout << "Invalid setup command. Please try again" << endl;
                            break;
                        }
                    }
                    if (setUpComplete) break;
                }
            }
            default: {
                break;
            }
        }
    }
    score->printScore();
}

