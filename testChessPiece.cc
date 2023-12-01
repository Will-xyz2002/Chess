//-----------------------------------------------------
// now the testpiece only support king and bishop
//-----------------------------------------------------
#include "bishop.h"
#include "king.h"
#include "empty.h"
#include <memory>
#include <iostream>
#include <string>
using namespace std;
// this is a test harness for testing all the features of bishop.
int main(){
    ChessSquare initialPosition(3, 3);
    Empty temp = Empty(initialPosition);
    int choice;
    string piece;
    while (true){
        cout << "select a test to do:" << endl;
        cout << "1. Valid Movement Test" << endl;
        cout << "2. Invalid Movement Test" << endl;
        cout << "3. Path Generation Test" << endl;
        cout << "4. Board Boundary Test" << endl;
        cout << "5. No Movement Test" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()){
            cout << "End of input. Exiting..." << endl;
            return 0;
        }
        if (choice == 0){
            cout << "exiting the program..." << endl;
            return 0;
        }
        cout << "Which chess piece you wanna test? Enter piece: " << endl;
        cin >> piece;
        std::unique_ptr<ChessPiece> initial_piece;
        if (piece == "k"){ // test for king
            initial_piece = make_unique<King>(ChessColour::White, initialPosition); 
        }
        else if (piece == "b"){ //test for bishop
            initial_piece = make_unique<Bishop>(ChessColour::White, initialPosition);
        }
        else{
            cout << "only available test are b and k" << endl;
            continue;
        }
        cout << "input two integers, indicate row and column" << endl;
        ChessSquare destination(0, 0);
        ChessPiece dest_piece = Empty(destination);
        int row, col;
        switch(choice){
            case 1:  // valid move test;
                cin >> row >> col;
                dest_piece.setCoords(row, col);
                
                if (initial_piece->isValidMove(dest_piece)){
                    cout << "ValidMove Test passed!!" << endl;
                }
                else{
                    cout << "ValidMove Test NOT passed!!" << endl;
                }
                break;
            case 2: // invalid move test
                cin >> row >> col;
                dest_piece.setCoords(row, col);
                if (!initial_piece->isValidMove(dest_piece)){
                    cout << "InvalidMove test passed!!" << endl;
                }
                else{
                    cout << "InvalidMove test not passed!!" << endl;
                }
                break;
            case 3: //path generation test
                cin >> row >> col;
                dest_piece.setCoords(row, col);
                if (initial_piece->isValidMove(dest_piece)){
                    vector<ChessSquare> result = initial_piece->generatePath(dest_piece);
                    cout << "The path is :" << endl;
                    for (auto &p : result){
                        cout << "Row is :" << p.getRow();
                        cout << " Column is :" << p.getColumn() << endl;
                    }
                }
                else{
                    cout << "Input destination is not valid!" << endl;
                }
                break;
            case 4: // Board Boundary Test
                cout << "Testing board boundary by moving to your next input:" << endl;
                cout << "input two integers that are row and column which is out of bound: (can be 8 8 or 10 10)" << endl;
                cin >> row >> col;
                dest_piece.setCoords(row, col);
                if (!initial_piece->isValidMove(dest_piece)) {
                    cout << "BoardBoundary test passed!!" << endl;
                } else {
                    cout << "BoardBoundary test NOT passed!!" << endl;
                }
                break;

            case 5: // No Movement Test
                cout << "Testing no movement by staying at (3, 3)" << endl;
                if (!initial_piece->isValidMove(temp)) {
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

