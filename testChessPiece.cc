//-----------------------------------------------------
// now the testpiece support every chesspiece
//-----------------------------------------------------
#include "bishop.h"
#include "king.h"
#include "empty.h"
#include "knight.h"
#include "pawn.h"
#include "rook.h"
#include "queen.h"

#include <memory>
#include <iostream>
#include <string>
using namespace std;
// this is a test harness for testing all the features of bishop.
int main(){

    int choice;
    string piece;
    string piece_colour;

    while (true){
        ChessSquare initialPosition(0, 0);
        std::unique_ptr<ChessPiece> initial_piece = nullptr;
        std::unique_ptr<ChessPiece> final_piece = nullptr;
        int row, col, init_row, init_col;
        cout << "select a test to do:" << endl;
        cout << "1. Valid Movement Test" << endl;
        cout << "2. Path Generation Test" << endl;
        cout << "3. Board Boundary Test" << endl;
        cout << "4. No Movement Test" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        // check if it's the end of file
        if (cin.fail()){
            cout << "End of input. Exiting..." << endl;
            return 0;
        }

        // check if the user wanna quit
        if (choice == 0){
            cout << "exiting the program..." << endl;
            return 0;
        }
        // ______________________set of the initial piece_______________________
        // get the chesstype for the testing
        cout << "Which chess piece you wanna test? Enter piece: " << endl;
        cin >> piece;
        
        // assign the correct type
        if (piece == "k"){ // assign the piece to be king
            initial_piece = make_unique<King>(ChessColour::White, initialPosition); 
        }
        else if (piece == "b"){ // assign the piece to be bishop
            initial_piece = make_unique<Bishop>(ChessColour::White, initialPosition);
        }
        else if (piece == "q"){ // assign the piece to be queen
            initial_piece = make_unique<Queen>(ChessColour::White, initialPosition);
        }
        else if (piece == "p"){ // assign the piece to be pawn
            initial_piece = make_unique<Pawn>(ChessColour::White, initialPosition);
        }
        else if (piece == "r"){ // assign the piece to be rook
            initial_piece = make_unique<Rook>(ChessColour::White, initialPosition);
        }
        else if (piece == "k"){ // assign the piece to be knight
            initial_piece = make_unique<Knight>(ChessColour::White, initialPosition);
        }
        else if (piece == "e"){ // assign the piece to be empty
            initial_piece = make_unique<Empty>(initialPosition);
        }
        else {
            cout << "enter valid type" << endl;
            continue;
        }

        // set the initial position of the piece
        cout << "Input the initial position(row follwed by column) of the piece: " << endl;
        cin >> init_row >> init_col;
        initial_piece->setCoords(init_row, init_col);
        

        // set the colour of the piece
        cout << "Input the colour of the piece, enter w or b or n " << endl;
        cin >> piece_colour;
        if (piece_colour == "w"){
            initial_piece->setColour(ChessColour::White);
        }
        else if (piece_colour == "b"){
            initial_piece->setColour(ChessColour::Black);
        }
        else if (piece_colour == "n"){
            initial_piece->setColour(ChessColour::None);
        }
        else{
            cout << "input w(white) or b(black) or n(None), try again." << endl;
            continue;
        }
        // _____________________end of setting of the initial piece_______________________

        // ______________________set of the final piece_______________________
        cout << "Which chess piece you want for the final_piece? Enter piece: " << endl;
        cin >> piece;
        // assign the correct type
        if (piece == "k"){ // assign the piece to be king
            final_piece = make_unique<King>(ChessColour::White, initialPosition); 
        }
        else if (piece == "b"){ // assign the piece to be bishop
            final_piece = make_unique<Bishop>(ChessColour::White, initialPosition);
        }
        else if (piece == "q"){ // assign the piece to be queen
            final_piece = make_unique<Queen>(ChessColour::White, initialPosition);
        }
        else if (piece == "p"){ // assign the piece to be pawn
            final_piece = make_unique<Pawn>(ChessColour::White, initialPosition);
        }
        else if (piece == "r"){ // assign the piece to be rook
            final_piece = make_unique<Rook>(ChessColour::White, initialPosition);
        }
        else if (piece == "k"){ // assign the piece to be knight
            final_piece = make_unique<Knight>(ChessColour::White, initialPosition);
        }
        else if (piece == "e"){ // assign the piece to be empty
            final_piece = make_unique<Empty>(initialPosition);
        }
        else {
            cout << "enter valid type" << endl;
            continue;
        }

        // set the position for the final_piece
        cout << "Input the final position(row follwed by column) of the piece: " << endl;
        cin >> row >> col;
        final_piece->setCoords(row, col);

        // set the colour of the final_piece
        cout << "Input the colour of the final piece, enter w or b or n " << endl;
        cin >> piece_colour;
        if (piece_colour == "w"){
            initial_piece->setColour(ChessColour::White);
        }
        else if (piece_colour == "b"){
            initial_piece->setColour(ChessColour::Black);
        }
        else if (piece_colour == "n"){
            initial_piece->setColour(ChessColour::None);
        }
        else{
            cout << "input w(white) or b(black) or n(None), try again." << endl;
            continue;
        }
        // _________________________end of setting final_piece___________________________________

        switch(choice){
            case 1:  // valid move test;
                if (initial_piece->isValidMove(*final_piece)){
                    cout << "ValidMove Test passed!!" << endl;
                }
                else{
                    cout << "NOT a valid move!!" << endl;
                }
                break;

            case 2: //path generation test
                if (initial_piece->isValidMove(*final_piece)){
                    vector<ChessSquare> result = initial_piece->generatePath(*final_piece);
                    cout << "The path is :" << endl;
                    for (auto &p : result){
                        cout << "Coordinate : (" << p.getRow() << ", " << p.getColumn() << ")" << endl;
                    }
                }
                else{
                    cout << "Input destination is not valid!" << endl;
                }
                break;
            case 3: // Board Boundary Test
                if (!initial_piece->isValidMove(*final_piece)) {
                    cout << "BoardBoundary test passed!!" << endl;
                } else {
                    cout << "BoardBoundary test NOT passed!!" << endl;
                }
                break;

            case 4: // No Movement Test
                if (!initial_piece->isValidMove(*final_piece)) {
                    cout << "NoMovement test passed!!" << endl;
                } else {
                    cout << "NoMovement test NOT passed!!" << endl;
                }
                break;

            default:
                cout << "invalid choice. Try again." << endl;
        }
    }
}

