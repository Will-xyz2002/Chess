#include "chessGame.h"
#include "chessBoard.h"
#include "humanPlayer.h"
#include "computerPlayer.h"
#include "graphicsdisplay.h"
#include "scoreBoard.h"
#include "window.h"
#include <iostream>
#include <string>
#include <memory>

using namespace std;


enum class Command {GAME, MOVE, RESIGN, SETUP, ADD_PIECE, REMOVE_PIECE, CHANGE_PLAYER, DONE, NONE, RESET, SCORE};

Command convertCommand(string command) {
    if (command == "game" || command == "g") return Command::GAME;
    if (command == "move" || command == "m") return Command::MOVE;
    if (command == "resign" || command == "r") return Command::RESIGN;
    if (command == "setup" || command == "s") return Command::SETUP;
    if (command == "+") return Command::ADD_PIECE;
    if (command == "-") return Command::REMOVE_PIECE;
    if (command == "done" || command == "d") return Command::DONE;
    if (command == "=") return Command::CHANGE_PLAYER;
    if (command == "reset") return Command::RESET;
    if (command == "score") return Command::SCORE;
    return Command::NONE;
}


std::shared_ptr<Player> assignPlayer(string p, ChessColour colour) {
    shared_ptr<Player> player = nullptr;
    if (p == "human" || p == "h") {
        player = std::move(make_shared<HumanPlayer>(colour));
        return player;
    }
    else if (p == "computer[1]" || p == "c1") {
        player = std::move(make_shared<ComputerPlayer>(colour, 1));
        return player;
    }
    else if (p == "computer[2]" || p == "c2") {
        player = std::move(make_shared<ComputerPlayer>(colour, 2));
        return player;
    }
    else if (p == "computer[3]" || p == "c3") {
        player = std::move(make_shared<ComputerPlayer>(colour, 3));
        return player;
    }
    else if (p == "computer[4]" || p == "c4") {
        player = std::move(make_shared<ComputerPlayer>(colour, 4));
        return player;
    }
    throw std::logic_error("Cannot assign player. Please try again.");
}


int main(void) {
    string command;
    unique_ptr <ChessGame> game = nullptr;
    unique_ptr <ScoreBoard> score = std::move(make_unique<ScoreBoard>());
    shared_ptr <Player> whitePlayer = nullptr;
    shared_ptr <Player> blackPlayer = nullptr;
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
                    if (whitePlayer != nullptr) whitePlayer.reset();
                    if (blackPlayer != nullptr) blackPlayer.reset();
                    try {
                        whitePlayer = std::move(assignPlayer(player1, ChessColour::White));
                        blackPlayer = std::move(assignPlayer(player2, ChessColour::Black));
                        if (game != nullptr) game.reset();
                        if (!setup) board.init();
                        game = std::move(make_unique<ChessGame>(board, isWhiteTurn, whitePlayer, blackPlayer));
                        gameIsOn = true;
                    } catch (std::logic_error &e) {
                        cout << e.what() << endl;
                    }
                }
                break;
            }
            case Command::MOVE: { // player move piece
                if (!gameIsOn) {
                    cout << "No game exist. Please try again" << endl;
                    break;
                }
                if (game->currentPlayerIsComputer()) {
                    game->makeAMove();
                }
                else {
                    string initial;
                    string dest;
                    if (cin >> initial && cin >> dest) {
                        game->makeAMove(initial, dest);
                    }
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
                    board.emptyBoard();
                    isWhiteTurn = true;
                    setup = false;
                    gameIsOn = false;
                }
                break;
            }
            case Command::RESET:{ // reset the scoreboard
                cout << "Resetting the Score Board..." << endl;
                score->reset();
                score->printScore();
            }
            case Command::SCORE: { // let the player know the current score
                cout << "Printing out the current score..." << endl;
                score->printScore();
            }
            case Command::SETUP: { // setting up the board
                ChessBoard temp = board;
                std::unique_ptr<GraphicsDisplay> graphicsDisplay = std::make_unique<GraphicsDisplay>(BOARD_DIMENSION);
                graphicsDisplay->setBoard(temp);
                temp.attach(graphicsDisplay.get()); 
                graphicsDisplay->drawGrid(); 
                setup = true;
                bool setUpComplete = false;
                cout << "Currently on setup mode" << endl;
                cout << temp;
                while (cin >> command) {
                    switch (convertCommand(command)) {
                        case Command::ADD_PIECE: { // add a piece to the board
                            char pieceType;
                            string position;
                            if (cin >> pieceType && cin >> position) {
                                temp.addPiece(pieceType, position);
                                cout << temp;
                            }
                            break;
                        }
                        case Command::REMOVE_PIECE: { // remove a piece from the board
                            string position;
                            if (cin >> position) temp.removePiece(position);
                            cout << temp;
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
                            if (temp.isValidBoard()) {
                                board = temp;
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

